#ifndef _DEVICE_C_DEVICEAPPLE_H_
#define _DEVICE_C_DEVICEAPPLE_H_

#include "device/IDevice.h"
#include "render/IRenderDriver.h"

namespace se
{
    namespace device
    {
        class CDeviceApple : public IDevice
        {
        public:
            CDeviceApple(render::IRenderDriver *pRenderdriver, int width, int height);
            virtual ~CDeviceApple(){}
            virtual void SwapBuffers();
            virtual int GetWindowWidth();
            virtual int GetWindowHeight();
            virtual unsigned long long GetSystemRunTime();
            virtual void Sleep(unsigned long ms);
            virtual void OnSize(int iPosX, int iPosY, int iWidth, int iHeight);
            virtual void DrawBuffer(ubyte *buffer);
            virtual void SetDrawCallback(DrawCallback callback);
            virtual bool Run();
        private:
            int m_iWidth;
            int m_iHeight;
            DrawCallback m_drawCallback;
        };
    }
}

#endif
