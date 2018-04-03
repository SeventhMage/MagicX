#include "CRenderQueue.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{

		CRenderQueue::CRenderQueue(IMaterial *pMaterial)
			:m_pMaterial(pMaterial)
		{			
			m_vaoId = CSoftEngine::GetRenderer()->CreateVAO();			
		}

		CRenderQueue::~CRenderQueue()
		{			
			CSoftEngine::GetRenderer()->DestroyVAO(m_vaoId);			
		}

		void CRenderQueue::AddRenderCell(IRenderCell *pCell)
		{
			m_RenderCellList.push_back(pCell);
			pCell->SetRenderQueue(this);
		}

		void CRenderQueue::Clear()
		{
			m_RenderCellList.clear();
		}

		void CRenderQueue::Render(scene::ICamera *pCamera)
		{			
			CSoftEngine::GetRenderer()->EnableVertexArrayObject(m_vaoId);
			
			if (m_pMaterial)
			{
				IShaderProgram *pShaderProgram = m_pMaterial->GetShaderProgram();
				if (pShaderProgram)
				{
					CSoftEngine::GetRenderer()->UseShaderProgram(pShaderProgram->GetID());

					math::CMatrix4 viewMat = pCamera->GetViewMatrix();
					math::CMatrix4 projMat = pCamera->GetProjectionMatrix();

					float ambientCoe = m_pMaterial->GetAmbientCoefficient();
					float diffuseCoe = m_pMaterial->GetDiffuseCoefficient();
					float specularCoe = m_pMaterial->GetSpecularCoefficient();
					int specularityCoe = m_pMaterial->GetSpecularityCoefficient();

					pShaderProgram->SetUniform(render::UN_VIEW_MAT,
						viewMat.m, SE_FLOAT, sizeof(viewMat.m));
					pShaderProgram->SetUniform(render::UN_PROJ_MAT,
						projMat.m, SE_FLOAT, sizeof(projMat.m));
					pShaderProgram->SetUniform(render::UN_COLOR,
						m_pMaterial->GetColor().c, SE_FLOAT, sizeof(m_pMaterial->GetColor().c));
					pShaderProgram->SetUniform(render::UN_AMBIENT_COEFFICIENT,
						&ambientCoe, SE_FLOAT, sizeof(float));;
					pShaderProgram->SetUniform(render::UN_DIFFUSE_COEFFICIENT,
						&diffuseCoe, SE_FLOAT, sizeof(float));;
					pShaderProgram->SetUniform(render::UN_SPECULAR_COEFFICIENT,
						&specularCoe, SE_FLOAT, sizeof(float));;
					pShaderProgram->SetUniform(render::UN_SPECULARITY_COEFFICIENT,
						&specularityCoe, SE_FLOAT, sizeof(int));

					for (auto it = m_RenderCellList.begin(); it != m_RenderCellList.end(); ++it)
					{
						IRenderCell *pRenderCell = *it;
						if (pRenderCell)
						{
							pRenderCell->BindShaderParams(pShaderProgram);

							uint bufferId = pRenderCell->GetBufferID();
							uint textureId = pRenderCell->GetTextureID();

							CSoftEngine::GetRenderer()->BindBuffer(bufferId);
							CSoftEngine::GetRenderer()->BindTexture(textureId);

							CSoftEngine::GetRenderer()->DrawElements();
						}
					}
				}
				
			}			

		}		
	}
}