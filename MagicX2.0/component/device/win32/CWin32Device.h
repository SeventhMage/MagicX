#ifndef _MX_DEVICE_WIN32DEVICE_H_
#define _MX_DEVICE_WIN32DEVICE_H_
#include "device/IDevice.h"

namespace mx
{
	namespace device
	{
		class CWin32Device : public IDevice
		{
		public:
			CWin32Device(uint uPosX, uint uPosY, uint uWidth, uint uHeight, bool bFullScreen = false);
			virtual ~CWin32Device();
			virtual bool SetupDriver(IDeviceDriver *driver);
			virtual render::IRenderer *GetRenderer();
			virtual void SwapBuffers();
			virtual uint GetWidth(){ return m_uWidth; }
			virtual uint GetHeight(){ return m_uHeight; }
			virtual long GetSystemRunTime();
			virtual void Sleep(unsigned long ms);

			virtual bool Run();

			virtual void OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight);
		private:
			IDeviceDriver *m_driverList[E_DDT_NUM];
			HWND m_hWnd;
			uint m_uPosX;
			uint m_uPosY;
			uint m_uWidth;
			uint m_uHeight;
		};
	}
}

#endif
