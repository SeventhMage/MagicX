#ifndef _DEVICE_C_GESTURE_H_
#define _DEVICE_C_GESTURE_H_

#include "device/IGestureEvent.h"

#include <map>

namespace se
{
	namespace device
	{
		class CGesture : public IGestureEvent
		{
		public:

			virtual void SubscribeCallback(GestureCallback callback, void *obj);
			virtual void UnSubscribeCallback(GestureCallback callback);
		private:
			std::map<GestureCallback, void *>m_mapGestureCallback;
		};
	}
}

#endif