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

		void CRenderQueue::Render(const math::CMatrix4 &viewMat, const math::CMatrix4 &projMat)
		{			
			CSoftEngine::GetRenderer()->EnableVertexArrayObject(m_vaoId);
			
			if (m_pMaterial)
			{
				IShaderProgram *pShaderProgram = m_pMaterial->GetShaderProgram();
				if (pShaderProgram)
				{
					CSoftEngine::GetRenderer()->UseShaderProgram(pShaderProgram->GetID());

					pShaderProgram->SetUniform(render::UN_VIEW_MAT,
						viewMat.m, SE_FLOAT, sizeof(viewMat.m));
					pShaderProgram->SetUniform(render::UN_PROJ_MAT,
						projMat.m, SE_FLOAT, sizeof(projMat.m));
					pShaderProgram->SetUniform(render::UN_COLOR,
						m_pMaterial->GetColor().c, SE_FLOAT, sizeof(projMat.m));
					

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