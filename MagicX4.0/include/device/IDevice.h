#ifndef _MX_I_DEVICE_H_
#define _MX_I_DEVICE_H_

namespace mx
{
	enum EDeviceType
	{
		DT_WIN,
		DT_IOS,
		DT_ANDROID,
	};
	class IDevice
	{
	public:
		virtual EDeviceType GetType() const = 0;
		virtual void SwapBuffers() = 0;
		virtual int GetWindowWidth() const = 0;
		virtual int GetWindowHeight() const = 0;
		virtual unsigned long long GetSystemRunTime() const = 0;
		virtual void Sleep(unsigned long ms) = 0;
		virtual void OnSize(int iPosX, int iPosY, int iWidth, int iHeight) = 0;
		virtual bool Run() = 0;
	};
}

#endif