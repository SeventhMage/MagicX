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
            , m_aabbox(-.1f, -.1f, -.1f, .1f, .1f, .1f)
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
                        CVector3 vert( ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset],  ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 1],  ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 2]);
                        m_aabbox.Expand(vert);
                    }
                }
            }
        }

		void CEntity::Update(int delta)
		{			
			//更新矩阵等uniform			
			const CMatrix4 &worldMat = m_pSceneNode->GetAbsluateMatrix();
			CMatrix4 normalMat;
			CMatrix4 temp = worldMat;
			temp.SetTranslation(CVector3(0, 0, 0));			
			temp.GetInverse(normalMat);
			temp = normalMat;
			temp.GetTransposed(normalMat);
			m_pSceneNode->GetRotation();			

			IScene *pScene = CSoftEngine::GetSceneManager()->GetCurrentScene();
			if (pScene)
			{
				ICamera *pCamera = pScene->GetCamera();
				if (pCamera)
				{
                    const CFrustum &frustum = pCamera->GetFrustum();
                    CAABBox box = m_aabbox;
                    box.Transform(worldMat);
                    
					//if (!frustum.Culled(box))
					{
						m_pRenderCell->SetShaderParam(render::UN_WORLD_MAT, worldMat.m, SE_FLOAT, sizeof(worldMat.m));
						m_pRenderCell->SetShaderParam(render::UN_NORMAL_MAT, normalMat.m, SE_FLOAT, sizeof(normalMat.m));

						//加入到渲染队列
						CSoftEngine::GetRenderer()->SubmitRenderCell(m_pRenderCell);
					}

				}
			}
		}
	}
}
