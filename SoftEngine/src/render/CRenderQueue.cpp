#include "CRenderQueue.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{

		CRenderQueue::CRenderQueue(const char *material)
		{
			m_materialId = CSoftEngine::GetMaterialManager()->CreateMaterial(material);
		}

		CRenderQueue::~CRenderQueue()
		{
			CSoftEngine::GetMaterialManager()->DestroyMaterial(m_materialId);
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