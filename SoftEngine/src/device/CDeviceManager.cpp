#include "CDeviceManager.h"
#ifdef WIN32
#include "win32/CDeviceWin32.h"
#endif

namespace se
{
	namespace device
	{


		CDeviceManager::CDeviceManager()
			:m_pDevice(nullptr)
		{

		}

		CDeviceManager::~CDeviceManager()
		{

		}

		IDevice * CDeviceManager::CreateDevice(render::IRenderDriver *renderDriver, int x, int y, int width, int height, bool bFullScreen /* = false */)
		{
#ifdef WIN32
			m_pDevice = new CDeviceWin32(renderDriver, x, y, width, height, bFullScreen);
#endif						
			return m_pDevice;
		}

	}
}