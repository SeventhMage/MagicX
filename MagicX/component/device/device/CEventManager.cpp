#include "../include/CEventManager.h"
#include "common/mxDef.h"
#include "CKeyEvent.h"

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
			SAFE_DEL(m_pKeyEvent);
		}
	}
}