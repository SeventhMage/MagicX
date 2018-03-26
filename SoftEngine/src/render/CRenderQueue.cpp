#include "CRenderQueue.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{

		CRenderQueue::CRenderQueue(const char *material)
		{
			m_materialId = CSoftEngine::GetMaterialManager()->CreateMaterial(material);
			m_vaoId = CSoftEngine::GetRenderer()->CreateVAO();
			m_pShaderProgram = CSoftEngine::GetRenderer()->CreateShaderProgram();
		}

		CRenderQueue::~CRenderQueue()
		{
			CSoftEngine::GetMaterialManager()->DestroyMaterial(m_materialId);
			CSoftEngine::GetRenderer()->DestroyVAO(m_vaoId);
			CSoftEngine::GetRenderer()->DestroyShaderProgram(m_pShaderProgram);
		}

		void CRenderQueue::AddRenderCell(IRenderCell *pCell)
		{
			m_RenderCellList.push_back(pCell);
		}

		void CRenderQueue::Clear()
		{
			m_RenderCellList.clear();
		}

		void CRenderQueue::Render()
		{
			CSoftEngine::GetRenderer()->EnableVertexArrayObject(m_vaoId);
			CSoftEngine::GetRenderer()->UseShaderProgram(m_pShaderProgram->GetID());

			for (auto it = m_RenderCellList.begin(); it != m_RenderCellList.end(); ++it)
			{
				IRenderCell *pRenderCell = *it;
				if (pRenderCell)
				{
					uint materialId = pRenderCell->GetMaterialID();
					uint bufferId = pRenderCell->GetBufferID();					
					uint textureId = pRenderCell->GetTextureID();
					IShaderProgram *pShaderProgram = pRenderCell->GetShaderProgram();
					CSoftEngine::GetRenderer()->Render(pShaderProgram, materialId, bufferId, textureId);

									
				}				
			}
		}

	}
}