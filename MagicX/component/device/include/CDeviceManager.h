#ifndef _MX_C_DEVICE_MANAGER_H_
#define _MX_C_DEVICE_MANAGER_H_

#include "common/CSingleton.h"
#include "common/mxDef.h"
#include "IDevice.h"

namespace mx
{
	namespace device
	{
		class CDeviceManager : public CSingleton<CDeviceManager>
		{
		public:
			friend class CSingleton<CDeviceManager>;

			IDevice *CreateDevice(uint uWidth, uint uHeight, bool bFullScreen = false);
			IDevice *GetDevice() { return m_device; };
		private:
			CDeviceManager();
			~CDeviceManager();
		private:
			IDevice *m_device;
		};
	}
}

#endif