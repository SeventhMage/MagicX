/************************************************************************/
/* 用户输入EVENT                                                        */
/************************************************************************/
#ifndef _MX_DEVICE_E_EVENT_H_
#define _MX_DEVICE_E_EVENT_H_

namespace se
{
	namespace device
	{
		enum EEventKeyPress
		{
			EKP_MOUSE_LBUTTON = 0,
			EKP_MOUSE_RBUTTON,

			EKP_KEYBOARD_SPACE,
			EKP_KEYBOARD_ESC,
			EKP_KEYBOARD_N,
			EKP_KEYBOARD_A,
			EKP_KEYBOARD_S,
			EKP_KEYBOARD_D,
			EKP_KEYBOARD_W,

			EKP_NUM,
		};

		enum EGestureType
		{
			GT_TAP = 0,
			GT_PAN,
			GT_PINCH,

			GT_COUNT,
		};
	}
}

#endif
