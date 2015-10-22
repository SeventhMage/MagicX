#ifndef _I_DEVICE_H_INC_
#define _I_DEVICE_H_INC_

#include "common/mxDef.h"
#include "IDeviceDriver.h"

namespace mx
{
	namespace device
	{
		class IDevice
		{
		public:
			IDevice(uint uWidth, uint uHeight, bool bFullScreen = false){};
			~IDevice(){};

			virtual bool SetupDriver(IDeviceDriver *driver) = 0;
			virtual IDeviceDriver *GetDeviceDriver(DeviceDriverType) = 0;

			virtual long GetSystemRunTime() = 0;
			virtual void Sleep(unsigned long ms) = 0;

			virtual void SwapBuffers() = 0;

			virtual int GetWidth() = 0;
			virtual int GetHeight() = 0;

			virtual void OnSize(int iLeft, int iTop, int iWidth, int iHeight) = 0;

			virtual bool Run() = 0;		
		};
	}	
}

#endif // !_I_DEVICE_H_INC_
