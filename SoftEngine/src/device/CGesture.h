#ifndef _DEVICE_C_GESTURE_H_
#define _DEVICE_C_GESTURE_H_

#include "device/IGestureEvent.h"

#include <vector>

namespace se
{
	namespace device
	{
		class CGesture : public IGestureEvent
		{
		public:

			virtual void SubscribeCallback(GestureCallback callback);
			virtual void UnSubscribeCallback(GestureCallback callback);
		protected:
			std::vector<GestureCallback>m_GestureCallback;
		};
	}
}

#endif
