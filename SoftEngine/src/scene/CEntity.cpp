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

				 m_pRenderCell = CSoftEngine::GetRenderer()->CreateRenderCell(m_bufferId, materialId, m_pModel->GetTextureID());
                 
                 CalcBox(m_pModel->GetVertices());
			 }
			 
		}

		CEntity::~CEntity()
		{
			CSoftEngine::GetRenderer()->DestroyBuffer(m_bufferId);
			CSoftEngine::GetRenderer()->DestroyRenderCell(m_pRenderCell);

			SAFE_DEL(m_pModel);
		}
        
        void CEntity::CalcBox(base::Vertices *pVertices)
        {
            for (uint i = 0; i < pVertices->count; ++i)
            {
                for (auto it = pVertices->format.begin(); it != pVertices->format.end(); ++it)
                {
                    if (it->attribute == base::VA_POSITION)
                    {
                        CVector3 vert( pVertices->pVertexData[i * pVertices->stride + it->offset],  pVertices->pVertexData[i * pVertices->stride + it->offset + 1],  pVertices->pVertexData[i * pVertices->stride + it->offset + 2]);
                        m_aabbox.Expand(vert);
                    }
                }
            }
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
                    CFrustum frustum = pCamera->GetFrustum();
                    CAABBox box = m_aabbox;
                    box.Transform(worldMat);
                    
					if (!frustum.Culled(box))
					{
						const CMatrix4 &viewMat = pCamera->GetViewMatrix();
						const CMatrix4 &projMat = pCamera->GetProjectionMatrix();
						render::IShaderProgram *pShaderProgram = m_pRenderCell->GetShaderProgram();
						if (pShaderProgram)
						{
							pShaderProgram->SetUniform(render::UN_WORLD_MAT,
								(ubyte *)&worldMat.m, sizeof(worldMat.m));
							pShaderProgram->SetUniform(render::UN_VIEW_MAT,
								(ubyte *)&viewMat.m, sizeof(viewMat.m));
							pShaderProgram->SetUniform(render::UN_PROJ_MAT,
								(ubyte *)&projMat.m, sizeof(projMat.m));
						}								

						//加入到渲染队列
						CSoftEngine::GetRenderer()->SubmitRenderCell(m_pRenderCell);
					}

				}
			}
		}
	}
}
