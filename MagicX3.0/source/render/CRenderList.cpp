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

		void CRenderList::BeginRender()
		{
			m_renderableList.clear();
		}

		void CRenderList::Render()
		{
			for (auto it = m_renderableList.begin(); it != m_renderableList.end(); ++it)
			{
				(*it)->Render();
			}
		}

	}
}