#ifndef _MX_C_WIN32_DEVICE_H_
#define _MX_C_WIN32_DEVICE_H_

#include "../include/IDevice.h"
#include "../include/CRenderDriver.h"
#include "common/mxDef.h"

#include <Windows.h>

namespace mx
{
	namespace device
	{
		class CWin32Device : public IDevice
		{
		public:
			CWin32Device(uint uWidth, uint uHeight, bool bFullScreen = false);
			virtual ~CWin32Device();
			
			virtual bool SetupDriver(IDeviceDriver *driver);
			virtual IDeviceDriver *GetDeviceDriver(DeviceDriverType driverType);

			virtual long GetSystemRunTime();
			virtual void Sleep(unsigned long ms);

			virtual bool Run();
			
			virtual void SwapBuffers();

			virtual int GetWidth() { return m_uWidth;}
			virtual int GetHeight() { return m_uHeight; }

			virtual void OnSize(int iLeft, int iTop, int iWidth, int iHeight);
		private:
			HWND m_hWnd;
			uint m_uWidth;
			uint m_uHeight;

			IDeviceDriver *m_deviceDriver[DDT_NUM];
		};
	}
}

#endif