#ifndef _DEVICE_I_EVENT_MANAGER_H_
#define _DEVICE_I_EVENT_MANAGER_H_

#include "base/CSingleton.h"
#include "device/IKeyEvent.h"
#include "device/IDevice.h"
#include "base/seType.h"
#include "IGestureEvent.h"
#include "EEvent.h"

namespace se
{
    namespace device
    {
        class IEventManager
        {
        public:
            virtual ~IEventManager(){}
            virtual IKeyEvent *GetKeyEvent() = 0;
            virtual void SetDevice(IDevice *device) = 0;
            virtual void OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight) = 0;
            
            virtual void OnTouchBegin(int pointID, int x, int y, uint classID, uint touchNum) = 0;
            virtual void OnTouchEnd(int pointID, int x, int y, uint classID, uint touchNum) = 0;
            virtual void OnTouchMove(int pointID, int x, int y, uint classID, uint touchNum) = 0;
            virtual void RegisterGestureCallback(EGestureType type, GestureCallback callback) = 0;
            virtual void UnRegisterGestureCallback(EGestureType type, GestureCallback callback) = 0;

        };
    }
}

#endif
