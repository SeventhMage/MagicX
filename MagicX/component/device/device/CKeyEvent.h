#ifndef _MX_DEVICE_C_KEY_EVENT_H_
#define _MX_DEVICE_C_KEY_EVENT_H_

#include "../include/IKeyEvent.h"

namespace mx
{
	namespace device
	{
		class CKeyEvent : public IKeyEvent
		{
		public:
			CKeyEvent();
			virtual ~CKeyEvent();

			virtual void Press(EVENT_KEYPRESS key);
			virtual void Up(EVENT_KEYPRESS key);
			virtual bool IsPress(EVENT_KEYPRESS key);

#ifdef WIN32
			void SetMousePosition(int x, int y) { m_mouseX = x; m_mouseY = y; }
			int GetMousePositonX() { return m_mouseX; }
			int GetMousePositionY() { return m_mouseY; }
#endif

		private:
			bool m_keys[EKP_NUM];

#ifdef WIN32
			int m_mouseX;
			int m_mouseY;
#endif
		};
	}
}

#endif
