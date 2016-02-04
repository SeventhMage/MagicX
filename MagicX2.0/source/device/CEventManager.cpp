#include "device/CEventManager.h"
#include "device/CKeyEvent.h"

namespace mx
{
	namespace device
	{
		CEventManager::CEventManager()
		{
			m_pKeyEvent = new CKeyEvent();
		}
		CEventManager::~CEventManager()
		{
			delete m_pKeyEvent;
			m_pKeyEvent = NULL;
		}

		void CEventManager::OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight)
		{
			if (m_pDevice)
				m_pDevice->OnSize(uPosX, uPosY, uWidth, uHeight);
		}
	}
}