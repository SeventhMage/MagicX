#include "../include/CDeviceManager.h"
#include "CWin32Device.h"

namespace mx
{
	namespace device
	{

		CDeviceManager::CDeviceManager()
			:m_device(NULL)
		{

		}

		CDeviceManager::~CDeviceManager()
		{
			SAFE_DEL(m_device);
		}

		IDevice * CDeviceManager::CreateDevice(uint uWidth, uint uHeight, bool bFullScreen /*= false*/)
		{
			m_device = new CWin32Device(uWidth, uHeight, bFullScreen);
			return m_device;
		}

	}
}