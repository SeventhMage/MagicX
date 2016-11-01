/************************************************************************/
/* 设备管理接口                                                         */
/************************************************************************/

#ifndef _MX_DEVICE_I_DEVICE_MANAGER_H_
#define _MX_DEVICE_I_DEVICE_MANAGER_H_

#include "IDevice.h"
#include "render/IRenderDriver.h"

namespace mx
{
	namespace device
	{
		class IDeviceManager
		{
		public:
			virtual ~IDeviceManager(){};

			virtual IDevice *CreateDevice(EDeviceType deviceType, render::IRenderDriver *renderDriver, int x, int y, int width, int height, bool bFullScreen = false) = 0;
			virtual IDevice *GetDevice() = 0;
		};
	}
}

#endif