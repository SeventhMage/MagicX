#include "CRenderList.h"
#include "mx.h"



namespace mx
{
	namespace render
	{
		

		CRenderList::CRenderList()
		{

		}

		CRenderList::~CRenderList()
		{
			for (auto it = m_renderableList.begin(); it != m_renderableList.end(); ++it)
			{
				if (*it)
					delete (*it);
			}
			m_renderableList.clear();
		}

		void CRenderList::AddRenderable(IRenderable *pRenderable)
		{
			m_renderableList.push_back(pRenderable);
		}

		void CRenderList::RemoveRenderable(IRenderable *pRenderable)
		{
			auto it = std::find(m_renderableList.begin(), m_renderableList.end(), pRenderable);
			if (it != m_renderableList.end())
			{
				m_renderableList.erase(it);
			}
		}

		void CRenderList::Render()
		{
			for (auto it = m_renderableList.begin(); it != m_renderableList.end(); ++it)
			{
				RENDERER->Render(*it);
			}
		}

		void CRenderList::Clear()
		{
			m_renderableList.clear();
		}



	}
}