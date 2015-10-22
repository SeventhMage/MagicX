#ifndef _MX_DEVICE_C_RENDER_DRIVER_H_
#define _MX_DEVICE_C_RENDER_DRIVER_H_

#include <Windows.h>
#include "../include/IDeviceDriver.h"

namespace mx
{
	namespace device
	{
		enum DriverType
		{
			DT_OPENGL,
			DT_DX9,
			DT_DX11,
		};

		class CRenderDriver : public IDeviceDriver
		{
		public:
			CRenderDriver();
			virtual ~CRenderDriver();

			virtual DeviceDriverType GetDriverType() { return m_deviceDriverType; };

			virtual bool SetupWin32Renderer(HDC hDC){ return false; }
			virtual bool SetupLinuxRenderer(){ return false; }
			virtual bool SetupMacRenderer(){ return false; }		

			virtual void OnSize(int iLeft, int iTop, int iWidth, int iHeight) {}

		private:
			DeviceDriverType m_deviceDriverType;
		};
	}
}

#endif