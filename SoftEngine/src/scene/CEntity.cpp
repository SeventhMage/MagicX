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
						const CMatrix4 &ProjMat = pCamera->GetProjectionMatrix();
						render::IShaderProgram *pShaderProgram = m_pRenderCell->GetShaderProgram();
						if (pShaderProgram)
						{
							pShaderProgram->SetUniform(render::UN_WORLD_MAT,
								(ubyte *)worldMat.m, sizeof(worldMat.m));
							pShaderProgram->SetUniform(render::UN_VIEW_MAT,
								(ubyte *)worldMat.m, sizeof(&viewMat.m));
							pShaderProgram->SetUniform(render::UN_PROJ_MAT,
								(ubyte *)worldMat.m, sizeof(ProjMat.m));
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