#ifndef _DEVICE_C_GESTURE_TAP_H_
#define _DEVICE_C_GESTURE_TAP_H_

#include "CGesture.h"

namespace se
{
	namespace device
	{
		class CGestureTap : public CGesture
		{
		public:
			CGestureTap();
			virtual ~CGestureTap();

			virtual void OnTouchBegin(int pointID, int x, int y, uint classID, uint touchNum);
			virtual void OnTouchEnd(int pointID, int x, int y, uint classID, uint touchNum);
			virtual void OnTouchMove(int pointID, int x, int y, uint classID, uint touchNum);
		};
	}
}

#endif