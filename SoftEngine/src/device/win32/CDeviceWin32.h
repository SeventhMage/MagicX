#ifndef _MX_DEVICE_C_DEVICE_WIN32_H_
#define _MX_DEVICE_C_DEVICE_WIN32_H_

#include "device/IDevice.h"
#include "render/IRenderDriver.h"

#include <windows.h>

namespace se
{
	namespace device
	{
		class CDeviceWin32 : public IDevice
		{
		public:
			CDeviceWin32(render::IRenderDriver *pRenderDriver, int x, int y, int width, int height, bool fullScreen = false);
			virtual ~CDeviceWin32();

			virtual void SwapBuffers();
			virtual int GetWindowWidth();
			virtual int GetWindowHeight();
			virtual unsigned long long GetSystemRunTime();
			virtual void Sleep(unsigned long ms);
			virtual void OnSize(int iPosX, int iPosY, int iWidth, int iHeight);
			virtual void DrawBuffer(ubyte *buffer);
			virtual void DrawText(int iPosX, int iPoxY, const char *str, int length);
			
			virtual bool Run();

			HWND GetHWnd() { return m_hWnd; }
			
		private:
			render::IRenderDriver *m_pRenderDriver;
			HWND m_hWnd;			
			int m_iWidth;
			int m_iHeight;
			bool m_bFullScreen;
			BITMAPINFO m_bmpInfo;
		};
	}
}

#endif