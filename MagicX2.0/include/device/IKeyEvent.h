#ifndef _MX_DEVICE_I_KEY_EVENT_H_
#define _MX_DEVICE_I_KEY_EVENT_H_

#include "IEvent.h"

namespace mx
{
	namespace device
	{
		class IKeyEvent : public IEvent
		{
		public:
			IKeyEvent() {};
			virtual ~IKeyEvent() {};

			virtual void Press(EVENT_KEYPRESS key) = 0;
			virtual void Up(EVENT_KEYPRESS key) = 0;
			virtual bool IsPress(EVENT_KEYPRESS key) = 0;

			virtual void SetMousePosition(int x, int y) = 0;
			virtual int GetMousePositonX() = 0;
			virtual int GetMousePositionY() = 0;
		};
	}
}

#endif
