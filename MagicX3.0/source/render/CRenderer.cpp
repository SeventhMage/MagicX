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
			m_pRenderList = new CRenderList();
		}

		CRenderer::~CRenderer()
		{
			if (m_pRenderDriver)
				delete m_pRenderDriver;
			if (m_pRenderList)
				delete m_pRenderList;;
		}

		IRenderable * CRenderer::CreateRenderable()
		{
			return new CRenderable(m_pRenderList);
		}

		void CRenderer::DestroyRenderable(IRenderable *pRenderable)
		{
			if (pRenderable && m_pRenderList)
			{
				m_pRenderList->RemoveRenderable(pRenderable);
				delete pRenderable;
			}
		}

		void CRenderer::Render()
		{
			if (m_pRenderList)
			{				
				m_pRenderList->Render(this);
				m_pRenderList->EndRender();
			}
		}


	}
}