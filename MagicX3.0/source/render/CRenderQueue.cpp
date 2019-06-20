#include "render/IRenderQueue.h"
#include "CRenderQueue.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		CRenderQueue::CRenderQueue(int materialId)
			:m_materialId(materialId)
		{
		}
		CRenderQueue::~CRenderQueue()
		{
	
		}
		void CRenderQueue::AddRenderable(IRenderable *renderable)
		{
			for (auto texture : m_mapSlotTexture)
			{
				renderable->SetTexture(texture.first, texture.second.texture);
			}
			m_vecRenderables.push_back(renderable);
		}

		void CRenderQueue::RemoveRenderable(IRenderable *renderable)
		{
			for (auto it = m_vecRenderables.begin(); it != m_vecRenderables.end(); ++it)
			{
				if (*it == renderable)
				{
					m_vecRenderables.erase(it);
					break;
				}
			}
		}

		void CRenderQueue::Clear()
		{
			m_vecRenderables.clear();
		}

		void CRenderQueue::Render()
		{
			for (auto &renderable : m_vecRenderables)
			{
				RENDERER->Render(renderable);
			}
		}


		void CRenderQueue::BindPhaseUniform()
		{
			IMaterial *pMaterial = RENDERER->GetMaterialManager()->GetMaterial(m_materialId);
			if (pMaterial)
			{
				IShaderProgram *pShaderProgram = pMaterial->GetShaderProgram();
				for (auto &texturePhase : m_mapSlotTexture)
				{
					int phaseid = texturePhase.second.phaseid;
					IRenderPhase *pRenderPhase = RENDERER->GetRenderPhaseManager()->GetRenderPhase(phaseid);
					if (pShaderProgram && pRenderPhase)
					{
						int slot = texturePhase.first;
						pShaderProgram->SetUniform(texturePhase.second.name.c_str(), &slot);
						IRenderTarget *pRenderTarget = pRenderPhase->GetRenderTarget();
						if (pRenderTarget)
						{
							texturePhase.second.texture = pRenderTarget->GetTexture(texturePhase.second.index);
						}
					}

				}
			}
		}

		void CRenderQueue::SetPhaseTexture(const char *name,int phaseid,  int slot, int index)
		{
			m_mapSlotTexture[slot].phaseid = phaseid;
			m_mapSlotTexture[slot].index = index;
			m_mapSlotTexture[slot].name = name;
			m_mapSlotTexture[slot].texture = nullptr;
		}


		IMaterial * CRenderQueue::GetMaterial() const
		{
			return RENDERER->GetMaterialManager()->GetMaterial(m_materialId);
		}

	}
}