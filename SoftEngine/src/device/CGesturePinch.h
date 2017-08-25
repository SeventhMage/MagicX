#ifndef _DEVICE_C_GESTURE_PINCH_H_
#define _DEVICE_C_GESTURE_PINCH_H_

#include "CGesture.h"

namespace se
{
	namespace device
	{
		class CGesturePinch : public CGesture
		{
		public:
			CGesturePinch();
			virtual ~CGesturePinch();

			virtual void OnTouchBegin(int pointID, int x, int y, uint classID, uint touchNum);
			virtual void OnTouchEnd(int pointID, int x, int y, uint classID, uint touchNum);
			virtual void OnTouchMove(int pointID, int x, int y, uint classID, uint touchNum);
		};
	}
}

#endif