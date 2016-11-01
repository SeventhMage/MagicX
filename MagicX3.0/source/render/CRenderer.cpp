#include "CRenderer.h"
#include "opengl/COpenGLDriver.h"

namespace mx
{
	namespace render
	{


		CRenderer::CRenderer(ERenderDriverType type)
		{
			switch (type)
			{
			case RDT_OPENGL:
				m_pRenderDriver = new COpenGLDriver();
				break;
			case RDT_DIRECTX:
				break;
			case RDT_SOFTWARE:
				break;
			default:
				break;
			}
		}

		CRenderer::~CRenderer()
		{

		}

		void CRenderer::Render()
		{
			if (m_pRenderDriver)
				m_pRenderDriver->Render();
		}

	}
}