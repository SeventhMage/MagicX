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

	}
}