#include "driver/CMXRenderDriver.h"
#include "Render.h"

namespace mx
{
	namespace driver
	{


		CMXRenderDriver::CMXRenderDriver(RendererType renderType)
			:m_renderer(NULL)
			, m_renderType(renderType)
		{

		}

		CMXRenderDriver::~CMXRenderDriver()
		{
			SAFE_DEL(m_renderer);
		}

		bool CMXRenderDriver::SetupWin32Renderer(HDC hDC)
		{
			m_renderer = CreateRendererWin32(m_renderType, hDC);
			if (m_renderer)
			{
				m_renderer->InitRendererWin32(hDC);
				return true;
			}
			
			return false;
		}

		bool CMXRenderDriver::SetupLinuxRenderer()
		{
			return false;
		}

		bool CMXRenderDriver::SetupMacRenderer()
		{
			return false;
		}

	}
}