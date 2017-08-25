#include "CGesture.h"

namespace se
{
	namespace device
	{


		void CGesture::SubscribeCallback(GestureCallback callback, void *obj)
		{
			if (m_mapGestureCallback.find(callback) == m_mapGestureCallback.end())
			{
				m_mapGestureCallback[callback] = obj;
			}
		}

		void CGesture::UnSubscribeCallback(GestureCallback callback)
		{
			auto it = m_mapGestureCallback.find(callback);
			if (it != m_mapGestureCallback.end())
			{
				m_mapGestureCallback.erase(it);
			}
		}

	}
}