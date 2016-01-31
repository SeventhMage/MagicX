/************************************************************************/
/* 设备相关接口，程序通过设备启动引擎                                    */
/************************************************************************/
#ifndef _MX_DEVICE_IDEVICE_H_
#define _MX_DEVICE_IDEVICE_H_

#include "mxType.h"
#include "IDeviceDriver.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace device
	{
		class IDevice
		{
		public:
			IDevice(){}
			virtual ~IDevice(){}
			virtual bool SetupDriver(IDeviceDriver *driver) = 0;
			virtual render::IRenderer *GetRenderer() = 0;
			virtual void SwapBuffers() = 0;
			virtual uint GetWidth() = 0;
			virtual uint GetHeight() = 0;
			virtual long GetSystemRunTime() = 0;
			virtual void Sleep(unsigned long ms) = 0;

			virtual bool Run() = 0;

			virtual void OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight) = 0;

		};
	}
}

#endif