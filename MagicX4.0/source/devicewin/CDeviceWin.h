#ifndef _MX_C_DEVICE_WIN_H_
#define _MX_C_DEVICE_WIN_H_

#include "device/IDevice.h"

namespace mx
{
	class CDeviceWin : public IDevice
	{
	public:
		CDeviceWin();
		~CDeviceWin();
	};
}

#endif