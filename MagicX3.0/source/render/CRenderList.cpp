#include "CRenderList.h"

#include <algorithm>

namespace mx
{
	namespace render
	{
		

		CRenderList::CRenderList()
		{

		}

		CRenderList::~CRenderList()
		{

		}

		void CRenderList::AddRenderable(IRenderable *pRenderable)
		{
			m_renderableList.push_back(pRenderable);
		}

		int CRenderList::GetRenderableCount()
		{
			return m_renderableList.size();
		}

		RENDER_LIST & CRenderList::GetRenderList()
		{
			return m_renderableList;
		}

		void CRenderList::EndRender()
		{
			m_renderableList.clear();
		}

		void CRenderList::Render(IRenderer *pRenderer)
		{
			if (pRenderer)
			{
				for (auto it = m_renderableList.begin(); it != m_renderableList.end(); ++it)
				{
					if ((*it)->IsActive())
					{
						pRenderer->Render(*it);
					}				
				}
			}
		}

		void CRenderList::RemoveRenderable(IRenderable *pRenderable)
		{
			auto it = std::find(m_renderableList.begin(), m_renderableList.end(), pRenderable);
			if (it != m_renderableList.end())
			{
				m_renderableList.erase(it);
			}
		}


	}
}