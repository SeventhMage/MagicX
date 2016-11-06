#include "CRenderer.h"
#include "opengl/COpenGLDriver.h"
#include "CRenderList.h"
#include "CRenderable.h"

namespace mx
{
	namespace render
	{


		CRenderer::CRenderer(IRenderDriver *pRenderDriver)
			:m_pRenderDriver(pRenderDriver)
		{
			
		}

		CRenderer::~CRenderer()
		{
			if (m_pRenderDriver)
				delete m_pRenderDriver;

			for (auto it = m_vecVertexArray.begin(); it != m_vecVertexArray.end(); ++it)
			{
				if (*it)
					delete (*it);
			}
			m_vecVertexArray.clear();
		}

		IRenderable * CRenderer::CreateRenderable(IRenderList *pRenderList)
		{
			return new CRenderable(pRenderList);
		}

		void CRenderer::DestroyRenderable(IRenderable *pRenderable)
		{
			if (pRenderable)
			{				
				pRenderable->RemoveFromRenderList();
				delete pRenderable;
			}
		}

		void CRenderer::AddVertexArrayObject(IVertexArrayObject *pObject)
		{
			auto it = std::find(m_vecVertexArray.begin(), m_vecVertexArray.end(), pObject);
			if (it == m_vecVertexArray.end())
			{
				m_vecVertexArray.push_back(pObject);
			}
		}

		void CRenderer::RemoveVertexArrayObject(IVertexArrayObject *pObject)
		{
			auto it = std::find(m_vecVertexArray.begin(), m_vecVertexArray.end(), pObject);
			if (it != m_vecVertexArray.end())
			{
				m_vecVertexArray.erase(it);
			}
		}
	}
}