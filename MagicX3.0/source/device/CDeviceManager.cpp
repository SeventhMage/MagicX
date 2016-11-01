#include "CDeviceManager.h"
#include "win32/CDeviceWin32.h"

namespace mx
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

		IDevice * CDeviceManager::CreateDevice(EDeviceType deviceType, render::IRenderDriver *renderDriver, int x, int y, int width, int height, bool bFullScreen /* = false */)
		{
			switch (deviceType)
			{
			case DT_WIN32:
			{
							 m_pDevice = new CDeviceWin32(renderDriver, x, y, width, height, bFullScreen);
			}
				break;
			case DT_LINUX:
				break;
			case DT_MAC:
				break;
			case DT_IOS:
				break;
			case DT_ANDROID:
				break;
			default:
				break;
			}

			return m_pDevice;
		}

	}
}