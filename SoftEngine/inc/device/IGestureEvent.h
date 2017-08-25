/*
 * Touch event for screen.
 */

#ifndef _I_DEVICE_GESTURE_EVENT_H_
#define _I_DEVICE_GESTURE_EVENT_H_

#include "IEvent"

namespace se {
    namespace device
    {
        class IGesutureEvent : public IEvent
        {
        public:
            virtual ~IGesutureEvent(){}
            
            virtual void Gap(int x, int y) = 0;
            virtual void Pinch() = 0;
            virtual void Rotation() = 0;
            virtual void Pan() = 0;
            virtual void LongPress() = 0;
            
        };
    }
}


#endif
