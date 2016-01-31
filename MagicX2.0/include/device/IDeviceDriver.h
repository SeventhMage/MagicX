/************************************************************************/
/* 设备驱动接口，渲染器安装在设备上需要实现此接口                       */
/************************************************************************/
#ifndef _MX_DEVICE_DEVICEDRIVER_H_
#define _MX_DEVICE_DEVICEDRIVER_H_

#ifdef WIN32
#include <windows.h>
#endif

namespace mx
{
	namespace device
	{
		enum EDeviceDriverType
		{
			E_DDT_RENDERER = 0,

			E_DDT_NUM,
		};
		class IDeviceDriver
		{
		public:
			IDeviceDriver(){}
			virtual ~IDeviceDriver(){}
			virtual EDeviceDriverType GetDriverType() = 0;
#ifdef WIN32
			virtual bool SetupWin32Driver(HDC hDC) = 0;
#endif			
		};
	}
}

#endif