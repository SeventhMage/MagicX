#include "CKeyEvent.h"
#include <string.h>


namespace se
{
	namespace device
	{
		CKeyEvent::CKeyEvent()
			:m_delta(0)
		{
			memset(m_keys, 0, sizeof(m_keys));
		}
		CKeyEvent::~CKeyEvent()
		{
		}
		void CKeyEvent::OnPress(EEventKeyPress key)
		{
			m_keys[key] = true;
		}
		void CKeyEvent::OnUp(EEventKeyPress key)
		{
			m_keys[key] = false;
		}
		bool CKeyEvent::IsPress(EEventKeyPress key)
		{
			return m_keys[key];
		}

		void CKeyEvent::OnWheel(int delta)
		{
			m_delta = delta;
		}

		int CKeyEvent::GetWheelDelta()
		{
			int delta = m_delta;
			m_delta = 0;
			return delta;
		}

	}
}