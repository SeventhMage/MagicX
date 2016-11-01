/************************************************************************/
/* 所有EVENT接口                                                        */
/************************************************************************/
#ifndef _MX_DEVICE_I_EVENT_H_
#define _MX_DEVICE_I_EVENT_H_

#include "EEvent.h"

namespace mx
{
	namespace device
	{
		class IEvent
		{
		public:
			IEvent() {};
			virtual~IEvent() {};
		};
	}
}

#endif
