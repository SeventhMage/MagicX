/************************************************************************/
/* 设置管理实现                                                         */
/************************************************************************/

#ifndef _MX_DEVICE_C_DEVICE_MANAGER_H_
#define _MX_DEVICE_C_DEVICE_MANAGER_H_

#include "device/IDeviceManager.h"

namespace mx
{
	namespace device
	{
		class CDeviceManager : public IDeviceManager
		{
		public:
			CDeviceManager();
			virtual ~CDeviceManager();
			
			virtual IDevice *CreateDevice(EDeviceType deviceType, render::IRenderDriver *renderDriver, int x, int y, int width, int height, bool bFullScreen = false);
			virtual IDevice *GetDevice() { return m_pDevice; };
		private:
			IDevice *m_pDevice;
		};
	}
}

#endif