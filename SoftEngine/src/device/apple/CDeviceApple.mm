#include "CDeviceApple.h"


#import <UIKit/UIKit.h>


namespace se
{
    namespace device
    {
        CDeviceApple::CDeviceApple(render::IRenderDriver *pRenderdriver, int width, int height)
        :m_iWidth(width)
        ,m_iHeight(height)
        ,m_drawCallback(nullptr)
        {
            render::SRenderContext context = {width, height};
            pRenderdriver->InitDriver(context);
        }
        
        void CDeviceApple::SwapBuffers()
        {
        }
        
        int CDeviceApple::GetWindowWidth()
        {
            return m_iWidth;
        }
        
        int CDeviceApple::GetWindowHeight()
        {
            return m_iHeight;
        }
        
        long CDeviceApple::GetSystemRunTime()
        {
            return 0;
        }
        
        void CDeviceApple::Sleep(unsigned long ms)
        {
            
        }
        
        void CDeviceApple::OnSize(int iPosX, int iPosY, int iWidth, int iHeight)
        {
            m_iWidth = iWidth;
            m_iHeight = iHeight;
        }
        
        void CDeviceApple::DrawBuffer(ubyte *buffer)
        {
            /*
            NSUInteger size = m_iWidth * m_iHeight * sizeof(uint);
            NSData *imageData = [[NSData alloc]initWithBytes:buffer length:size];
            UIImage* myImage = [ [ UIImage alloc ]initWithData:imageData ];
            
            CGRect myRect;
            
            myRect.origin.x = 0.0 ;
            myRect.origin.y = 0.0;
            myRect.size = myImage.size;
            [myImage drawInRect:myRect];
             */
            if (m_drawCallback)
                m_drawCallback(buffer);
        }
        
        void CDeviceApple::SetDrawCallback(DrawCallback callback)
        {
            m_drawCallback = callback;
        }
        
        bool CDeviceApple::Run()
        {
            return true;
        }
    }
}
