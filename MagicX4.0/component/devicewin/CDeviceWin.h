#ifndef _MX_C_DEVICE_WIN_H_
#define _MX_C_DEVICE_WIN_H_

#include "device/IDevice.h"
#include "render/IRenderer.h"

#include <Windows.h>

namespace mx
{
	class CDeviceWin : public IDevice
	{
	public:
		CDeviceWin(IRenderer *pRenderer, int x, int y, int width, int height, bool fullScreen = false);
		~CDeviceWin();
		
		virtual EDeviceType GetType() const { return DT_WIN; }		
		virtual void SwapBuffers();
		virtual int GetWindowWidth() const;
		virtual int GetWindowHeight() const;
		virtual unsigned long long GetSystemRunTime() const;
		virtual void Sleep(unsigned long ms);
		virtual void OnSize(int x, int y, int width, int height);
		virtual bool Run();
	private:
		IRenderer *m_pRenderer;
		HWND m_hWnd;
		int m_iWidth;
		int m_iHeight;
		bool m_bFullScreen;
	};
}

#endif