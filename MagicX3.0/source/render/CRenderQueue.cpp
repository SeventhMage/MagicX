#include "render/IRenderQueue.h"
#include "CRenderQueue.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		CRenderQueue::CRenderQueue(int materialId)
			:m_materialId(materialId)
			,m_phaseQuote(0)
		{
		}
		CRenderQueue::~CRenderQueue()
		{
		}
		void CRenderQueue::AddRenderable(IRenderable *renderable)
		{
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

		void CRenderQueue::SetPhaseQuote(int phaseId)
		{
			m_phaseQuote = phaseId;
		}

		void CRenderQueue::BindPhaseUniform()
		{
			IMaterial *pMaterial = RENDERER->GetMaterialManager()->GetMaterial(m_materialId);
			if (pMaterial)
			{

			}
		}

	}
}