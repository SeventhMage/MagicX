#include "driver/CMXRenderDriver.h"
#include "Render.h"
#include "CDeviceManager.h"

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
				IDevice *device = CDeviceManager::Instance()->GetDevice();
				if (device)
					m_renderer->SetViewport(0, 0, device->GetWidth(), device->GetHeight());
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

		void CMXRenderDriver::OnSize(int iLeft, int iTop, int iWidth, int iHeight)
		{
			m_renderer->SetViewport(iLeft, iTop, iWidth, iHeight);
		}

	}
}