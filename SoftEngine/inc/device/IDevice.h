/************************************************************************/
/* 设备相关接口，维护设备相关信息                                             */
/************************************************************************/
#ifndef _MX_DEVICE_IDEVICE_H_
#define _MX_DEVICE_IDEVICE_H_

#include "render/IRenderer.h"

namespace se
{
	namespace device
	{
		enum EDeviceType
		{
			DT_WIN32,			//win32
			DT_LINUX,			//linux
			DT_MAC,				//mac
			DT_IOS,				//ios
			DT_ANDROID,			//android

			DT_NUM,
		};

        typedef void (*DrawCallback)(ubyte *buffer);
		class IDevice
		{
		public:
			IDevice(){}
			virtual ~IDevice(){}
			virtual void SwapBuffers() = 0;
			virtual int GetWindowWidth() = 0;
			virtual int GetWindowHeight() = 0;
			virtual long GetSystemRunTime() = 0;
			virtual void Sleep(unsigned long ms) = 0;
			virtual void OnSize(int iPosX, int iPosY, int iWidth, int iHeight) = 0;
			virtual void DrawBuffer(ubyte *buffer){}
            virtual void SetDrawCallback(DrawCallback callback){};
            
			virtual bool Run() = 0;
		};
	}
}

#endif
