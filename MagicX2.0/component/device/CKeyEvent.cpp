#include "CKeyEvent.h"
#include <string.h>


namespace mx
{
	namespace device
	{
		CKeyEvent::CKeyEvent()
		{
			memset(m_keys, 0, sizeof(m_keys));
		}
		CKeyEvent::~CKeyEvent()
		{
		}
		void CKeyEvent::Press(EVENT_KEYPRESS key)
		{
			m_keys[key] = true;
		}
		void CKeyEvent::Up(EVENT_KEYPRESS key)
		{
			m_keys[key] = false;
		}
		bool CKeyEvent::IsPress(EVENT_KEYPRESS key)
		{
			return m_keys[key];
		}

	}
}