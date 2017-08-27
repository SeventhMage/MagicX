#ifndef _DEVICE_C_GESTURE_PAN_H_
#define _DEVICE_C_GESTURE_PAN_H_

#include "CGesture.h"

namespace se
{
	namespace device
	{
		class CGesturePan : public CGesture
		{
		public:
			CGesturePan();
			virtual ~CGesturePan();
			virtual void OnTouchBegin(int pointID, int x, int y, uint classID, uint touchNum);
			virtual void OnTouchEnd(int pointID, int x, int y, uint classID, uint touchNum);
			virtual void OnTouchMove(int pointID, int x, int y, uint classID, uint touchNum);
        private:
            SGesturePanArgs *m_panArgs;
            
		};
	}
}

#endif
