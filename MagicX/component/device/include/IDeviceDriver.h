#ifndef _MX_DEVICE_DRIVER_H_
#define _MX_DEVICE_DRIVER_H_

namespace mx
{
	namespace device
	{
		enum DeviceDriverType
		{			
			DDT_RENDERER = 0,

			DDT_NUM,
		};
		class IDeviceDriver
		{
		public:
			IDeviceDriver(){}
			virtual ~IDeviceDriver(){}

			virtual DeviceDriverType GetDriverType() = 0;
		};
	}
}

#endif