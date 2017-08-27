#include "CGesture.h"

#include <algorithm>

namespace se
{
	namespace device
	{


		void CGesture::SubscribeCallback(GestureCallback callback)
		{
            if (std::find(m_GestureCallback.begin(), m_GestureCallback.end(), callback) != m_GestureCallback.end())
            {
                m_GestureCallback.push_back(callback);
            }
		}

		void CGesture::UnSubscribeCallback(GestureCallback callback)
		{
            auto it = std::find(m_GestureCallback.begin(), m_GestureCallback.end(), callback);
            if (it != m_GestureCallback.end())
            {
                m_GestureCallback.erase(it);
            }
		}

	}
}
