#ifndef _MX_I_DEVICE_H_
#define _MX_I_DEVICE_H_

namespace mx
{
	class IDevice
	{
	public:
		virtual bool Run() = 0;
	};
}

#endif