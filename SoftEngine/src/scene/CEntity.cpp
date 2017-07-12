#include "CEntity.h"
#include "CSoftEngine.h"
#include "render/UniformDef.h"
#include "CModel.h"

namespace se
{
	namespace scene
	{
		CEntity::CEntity(const char *name, ISceneNode *pNode)
			:m_strEntityName(name)
			, m_pSceneNode(pNode)					
		{
			m_pModel = new CModel(name);						 
			 if (m_pModel)
			 {
				 int materialId = CSoftEngine::GetMaterialManager()->GetMaterialID(m_pModel->GetMaterialName().c_str());

				 m_bufferId = CSoftEngine::GetRenderer()->CreateBuffer();
				 			
				 //提交顶点数据到渲染器
				 CSoftEngine::GetRenderer()->BufferData(m_bufferId, m_pModel->GetVertices(), m_pModel->GetIndices());				 

				 m_pRenderCell = CSoftEngine::GetRenderer()->CreateRenderCell(m_bufferId, materialId, 0);
			 }
			 
		}

		CEntity::~CEntity()
		{
			CSoftEngine::GetRenderer()->DestroyBuffer(m_bufferId);
			CSoftEngine::GetRenderer()->DestroyRenderCell(m_pRenderCell);

			SAFE_DEL(m_pModel);
		}

		void CEntity::Update(int delta)
		{			
			//更新矩阵等uniform
			const CMatrix4 &worldMat = m_pSceneNode->GetAbsluateMatrix();
			IScene *pScene = CSoftEngine::GetSceneManager()->GetCurrentScene();
			if (pScene)
			{
				ICamera *pCamera = pScene->GetCamera();
				if (pCamera)
				{
					if (!Culled(pCamera))
					{
						const CMatrix4 &viewMat = pCamera->GetViewMatrix();
						const CMatrix4 &projMat = pCamera->GetProjectionMatrix();
						render::IShaderProgram *pShaderProgram = m_pRenderCell->GetShaderProgram();
						if (pShaderProgram)
						{
						/*	pShaderProgram->SetUniform(render::UN_WORLD_MAT,
								(ubyte *)&worldMat.m, sizeof(worldMat.m));*/
							pShaderProgram->SetUniform(render::UN_VIEW_MAT,
								(ubyte *)&viewMat.m, sizeof(viewMat.m));
							pShaderProgram->SetUniform(render::UN_PROJ_MAT,
								(ubyte *)&projMat.m, sizeof(projMat.m));

							static float rad = 0;
							rad += 0.1f;
							CMatrix4 modelMat;
							
							//modelMat.SetScale(CVector3(2.5f, 2.5f, 2.5f));
							modelMat.SetRotationRadians(rad, CVector3(0, 1, 0));

							pShaderProgram->SetUniform(render::UN_MODEL_MAT, (ubyte *)&modelMat.m, sizeof(modelMat.m));
						}								

						//加入到渲染队列
						CSoftEngine::GetRenderer()->SubmitRenderCell(m_pRenderCell);
					}

				}
			}
		}

		bool CEntity::Culled(ICamera *pCamera)
		{
			return false;
		}

	}
}