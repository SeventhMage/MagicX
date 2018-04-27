#ifndef _MX_DEVICE_E_EVENT_H_
#define _MX_DEVICE_E_EVENT_H_

namespace mx
{
	enum EEventType
	{
		ET_KEYBOARD,
		ET_MOUSE,

		ET_NUM,
	};

	enum EEventKeyPress
	{
		KP_MOUSE_LBUTTON = 0,
		KP_MOUSE_RBUTTON,

		KP_KEYBOARD_SPACE,
		KP_KEYBOARD_ESC,
		KP_KEYBOARD_N,

		KP_KEYBOARD_A,
		KP_KEYBOARD_D,
		KP_KEYBOARD_W,
		KP_KEYBOARD_S,

		KP_NUM,
	};
	
}

#endif
