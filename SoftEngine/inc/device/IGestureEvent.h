/*
 * Touch event for screen.
 */

#ifndef _I_DEVICE_GESTURE_EVENT_H_
#define _I_DEVICE_GESTURE_EVENT_H_

#include "IEvent.h"
#include "base/seType.h"

namespace se {
    namespace device
    {
		class IGestureArgs
		{
		public:
			IGestureArgs(){}
			~IGestureArgs(){}
		};		
		typedef void(*GestureCallback)(IGestureArgs *args);
        class IGestureEvent : public IEvent
        {
        public:
			virtual ~IGestureEvent(){}
			virtual void OnTouchBegin(int pointID, int x, int y, uint classID, uint touchNum) = 0;
			virtual void OnTouchEnd(int pointID, int x, int y, uint classID, uint touchNum) = 0;
			virtual void OnTouchMove(int pointID, int x, int y, uint classID, uint touchNum) = 0;   

			virtual void SubscribeCallback(GestureCallback callback, void *obj) = 0;
			virtual void UnSubscribeCallback(GestureCallback callback) = 0;
        };
    }
}


#endif
