#ifndef _DEVICE_C_DEVICEAPPLE_H_
#define _DEVICE_C_DEVICEAPPLE_H_

#include "device/IDevice.h"

namespace se
{
    namespace device
    {
        class CDeviceApple : public IDevice
        {
        public:
            CDeviceApple(int width, int height);
            virtual ~CDeviceApple(){}
            virtual void SwapBuffers();
            virtual int GetWindowWidth();
            virtual int GetWindowHeight();
            virtual long GetSystemRunTime();
            virtual void Sleep(unsigned long ms);
            virtual void OnSize(int iPosX, int iPosY, int iWidth, int iHeight);
            virtual void DrawBuffer(ubyte *buffer);
            
            virtual bool Run();
        private:
            int m_iWidth;
            int m_iHeight;
        };
    }
}

#endif
