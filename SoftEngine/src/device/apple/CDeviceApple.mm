#include "CDeviceApple.h"


namespace se
{
    namespace device
    {
        CDeviceApple::CDeviceApple(int width, int height)
        :m_iWidth(width)
        ,m_iHeight(height)
        {
            
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
            
        }
        
        bool CDeviceApple::Run()
        {
            return true;
        }
    }
}
