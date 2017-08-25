/************************************************************************/
/* The Keyboard EVENT                                                   */
/************************************************************************/
#ifndef _MX_DEVICE_I_KEY_EVENT_H_
#define _MX_DEVICE_I_KEY_EVENT_H_

#include "IEvent.h"

namespace se
{
	namespace device
	{
		class IKeyEvent : public IEvent
		{
		public:
			IKeyEvent() {};
			virtual ~IKeyEvent() {};

			virtual void OnPress(EEventKeyPress key) = 0;
			virtual void OnUp(EEventKeyPress key) = 0;
			virtual bool IsPress(EEventKeyPress key) = 0;
			virtual void OnWheel(int delta) = 0;

			virtual void SetMousePosition(int x, int y) = 0;
			virtual int GetMousePositonX() = 0;
			virtual int GetMousePositionY() = 0;
			virtual int GetWheelDelta() = 0;
		};
	}
}

#endif
