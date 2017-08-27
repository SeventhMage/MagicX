#ifndef _DEVICE_GESTURE_ARGS_H_
#define _DEVICE_GESTURE_ARGS_H_

namespace se {
    namespace device
    {
        struct IGestureArgs
        {
        public:
            IGestureArgs(){}
            virtual ~IGestureArgs(){}
        };
        
        struct SGesturePanArgs : public IGestureArgs
        {
            int startTouchX;
            int startTouchY;
            int curTouchX;
            int curTouchY;
        };
    }
}

#endif
