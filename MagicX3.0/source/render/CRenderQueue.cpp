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

		void CRenderQueue::AddPhaseQuote(int phaseId)
		{
			if (std::find(m_vecPhaseQuote.begin(), m_vecPhaseQuote.end(), phaseId) == m_vecPhaseQuote.end())
			{
				m_vecPhaseQuote.push_back(phaseId);
			}
		}

		void CRenderQueue::BindPhaseUniform()
		{
			IMaterial *pMaterial = RENDERER->GetMaterialManager()->GetMaterial(m_materialId);
			if (pMaterial)
			{
				IShaderProgram *pShaderProgram = pMaterial->GetShaderProgram();
				for (auto phaseid : m_vecPhaseQuote)
				{
					IRenderPhase *pRenderPhase = RENDERER->GetRenderPhaseManager()->GetRenderPhase(phaseid);
					if (pShaderProgram && pRenderPhase)
					{
						IRenderTarget *pRenderTarget = pRenderPhase->GetRenderTarget();
						if (pRenderTarget)
						{
							for (auto &texture : m_mapSlotTexture)
							{
								int flag = ERTF_COLOR_TEXTURE;
								do
								{
									if (texture.second.flag & flag)
									{
										ITexture *pTexture = pRenderTarget->GetTexture(flag);
										if (pTexture)
										{
											int slot = texture.first;
											pShaderProgram->SetUniform(texture.second.name.c_str(), &slot);
											texture.second.texture = pTexture;
											break;
										}
									}
									flag <<= 1;
								} while (flag <= ERTF_MAX_FLAG);
							}
						}

					}
				}
			}
		}

		void CRenderQueue::SetPhaseTexture(const char *name, int slot, int flag)
		{
			m_mapSlotTexture[slot].flag = flag;
			m_mapSlotTexture[slot].name = name;
			m_mapSlotTexture[slot].texture = nullptr;
		}


		IMaterial * CRenderQueue::GetMaterial() const
		{
			return RENDERER->GetMaterialManager()->GetMaterial(m_materialId);
		}

	}
}