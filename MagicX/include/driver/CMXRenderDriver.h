#ifndef _CMX_RENDER_DRIVER_H_
#define _CMX_RENDER_DRIVER_H_

#include "CRenderDriver.h"
#include "IRenderer.h"
#include "IDevice.h"

namespace mx
{
	using namespace render;
	using namespace device;
	namespace driver
	{
		class CMXRenderDriver : public device::CRenderDriver
		{
		public:
			CMXRenderDriver(RendererType renderType);
			virtual ~CMXRenderDriver();

			virtual bool SetupWin32Renderer(HDC hDC);
			virtual bool SetupLinuxRenderer();
			virtual bool SetupMacRenderer();

			virtual void OnSize(int iLeft, int iTop, int iWidth, int iHeight);

			IRenderer *GetRenderer(){ return m_renderer; }
		private:
			IRenderer *m_renderer;
			RendererType m_renderType;
		};
	}
}

#endif