#include "mx.h"
#include "device/IDevice.h"
#include "render/opengl/COpenGLDriver.h"
#ifdef WIN32
#include "device/win32/CWin32Device.h"
#endif

namespace mx
{
	IDevice * CreateDevice(uint uPosX, uint uPosY, uint uWidth, uint uHeight, bool bFullScreen /*= false*/)
	{
		IDevice *device = NULL;
#ifdef WIN32
		device = new CWin32Device(uPosX, uPosY, uWidth, uHeight, bFullScreen);
#endif
		render::IRenderDriver *renderDriver = new render::COpenGLDriver();
		device->SetupDriver(renderDriver);
		return device;
	}

	void DestroyDevice(IDevice *device)
	{
		if (device)
		{
			delete device;
			device = NULL;
		}
	}

}