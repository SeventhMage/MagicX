/************************************************************************/
/* 键盘EVENT实现                                                        */
/************************************************************************/
#ifndef _MX_DEVICE_C_KEY_EVENT_H_
#define _MX_DEVICE_C_KEY_EVENT_H_

#include "device/IKeyEvent.h"
#include "device/IDevice.h"

namespace se
{
	namespace device
	{
		class CKeyEvent : public IKeyEvent
		{
		public:
			CKeyEvent();
			virtual ~CKeyEvent();

			virtual void OnPress(EEventKeyPress key);
			virtual void OnUp(EEventKeyPress key);
			virtual bool IsPress(EEventKeyPress key);
			void OnWheel(int delta);

			void SetMousePosition(int x, int y) { m_mouseX = x; m_mouseY = y; }
			int GetMousePositonX() { return m_mouseX; }
			int GetMousePositionY() { return m_mouseY; }
			int GetWheelDelta();
		private:
			bool m_keys[EKP_NUM];

			int m_mouseX;
			int m_mouseY;

			int m_delta;
		};
	}
}

#endif
