/************************************************************************/
/* 键盘EVENT实现                                                        */
/************************************************************************/
#ifndef _MX_DEVICE_C_KEY_EVENT_H_
#define _MX_DEVICE_C_KEY_EVENT_H_

#include "device/IDevice.h"
#include "device/IEvent.h"

namespace mx
{
	class CKeyEvent : public IEvent
	{
	public:
		CKeyEvent();
		virtual ~CKeyEvent();

		virtual EEventType GetType() const { return ET_KEYBOARD; }
		void OnPress(EEventKeyPress key);
		void OnUp(EEventKeyPress key);
		bool IsPress(EEventKeyPress key);
		void OnWheel(int delta);

		void SetMousePosition(int x, int y) { m_mouseX = x; m_mouseY = y; }
		int GetMousePositonX() { return m_mouseX; }
		int GetMousePositionY() { return m_mouseY; }
		int GetWheelDelta();
	private:
		bool m_keys[KP_NUM];

		int m_mouseX;
		int m_mouseY;

		int m_delta;
	};
}

#endif
