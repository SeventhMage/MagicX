#include "CEntity.h"
#include "CSoftEngine.h"
#include "resource/IModel.h"
#include "render/SUniform.h"

namespace se
{
	namespace scene
	{
		CEntity::CEntity(const char *name, ISceneNode *pNode)
			:m_strEntityName(name)
			, m_pSceneNode(pNode)		
			, m_pRenderCell(nullptr)
		{
			 resource::IModel *pModel = dynamic_cast<resource::IModel *>(CSoftEngine::GetResourceManager()->LoadResource(name));
			 if (pModel)
			 {
				 int materialId = CSoftEngine::GetMaterialManager()->GetMaterialID(pModel->GetMaterial().c_str());

				 m_bufferId = CSoftEngine::GetRenderer()->CreateBuffer();
				 
				 const resource::Polygon &polygon = pModel->GetPolygon();

				 //提交顶点数据到渲染器
				 //CSoftEngine::GetRenderer()->BufferData();


				 CSoftEngine::GetResourceManager()->ReleaseResource(pModel);
			 }
		}

		CEntity::~CEntity()
		{
			CSoftEngine::GetRenderer()->DestroyBuffer(m_bufferId);
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
						CSoftEngine::GetRenderer()->UpdateUniform(render::UN_WORLD_MAT,
							(ubyte *)worldMat.m, sizeof(worldMat.m));
						CSoftEngine::GetRenderer()->UpdateUniform(render::UN_VIEW_MAT,
							(ubyte *)worldMat.m, sizeof(&viewMat.m));
						CSoftEngine::GetRenderer()->UpdateUniform(render::UN_PROJ_MAT,
							(ubyte *)worldMat.m, sizeof(ProjMat.m));

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