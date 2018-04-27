#include "device/CEventManager.h"
#include <string.h>
namespace mx
{

	CEventManager::CEventManager()
		:m_pDevice(nullptr)
	{
		memset(m_eventList, 0, sizeof(m_eventList));
	}
	CEventManager::~CEventManager()
	{
		for (int i = 0; ET_NUM; ++i)
		{			
			if (m_eventList[i])
				delete m_eventList[i];
		}
	}

	void CEventManager::OnSize(int x, int y, int widht, int height)
	{
		if (m_pDevice)
			m_pDevice->OnSize(x, y, widht, height);
	}

	void CEventManager::RegisterEvent(IEvent *pEvent)
	{
		if (!pEvent)
			return;

		if (m_eventList[pEvent->GetType()])
		{
			delete m_eventList[pEvent->GetType()];
		}

		m_eventList[pEvent->GetType()] = pEvent;
	}

}
