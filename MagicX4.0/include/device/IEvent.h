#ifndef _MX_DEVICE_I_EVENT_H_
#define _MX_DEVICE_I_EVENT_H_

#include "EEvent.h"

namespace mx
{

	class IEvent
	{
	public:
		IEvent() {};
		virtual~IEvent() {};
		virtual EEventType GetType() const = 0;
	};
	
}

#endif
