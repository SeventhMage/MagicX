#include "CRenderer.h"
#include "opengl/COpenGLDriver.h"
#include "CRenderList.h"
#include "CRenderable.h"
#include "CMaterial.h"

namespace mx
{
	namespace render
	{


		CRenderer::CRenderer(IRenderDriver *pRenderDriver)
			:m_pRenderDriver(pRenderDriver)
			, m_bRendShadow(false)
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
			return new CRenderable(pRenderList, this);
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

		IMaterial * CRenderer::CreateMaterial()
		{
			return new CMaterial();
		}

		void CRenderer::DestroyMaterial(IMaterial *pMaterial)
		{
			if (pMaterial)
				delete pMaterial;
		}

		void CRenderer::Render()
		{
			for (auto it = m_vecVertexArray.begin(); it != m_vecVertexArray.end(); ++it)
			{
				if (*it)
				{					
					(*it)->Render();
					(*it)->EndRender();
				}
			}
		}

		void CRenderer::EndRender()
		{
			for (auto it = m_vecVertexArray.begin(); it != m_vecVertexArray.end(); ++it)
			{
				if (*it)
				{
					(*it)->EndRender();
				}
			}
		}

	}
}