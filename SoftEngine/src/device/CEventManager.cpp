#include "device/CEventManager.h"
#include "CKeyEvent.h"
#include "CGesturePan.h"
#include "CGesturePinch.h"
#include "CGestureTap.h"

namespace se
{
	namespace device
	{
		CEventManager::CEventManager()
			:m_pDevice(nullptr)
		{
			m_pKeyEvent = new CKeyEvent();



		}
		CEventManager::~CEventManager()
		{
			SAFE_DEL(m_pKeyEvent);
		}

		void CEventManager::OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight)
		{
			if (m_pDevice)
				m_pDevice->OnSize(uPosX, uPosY, uWidth, uHeight);
		}

		void CEventManager::RegisterGestureCallback(EGestureType type, GestureCallback callback, void *obj)
		{
			if (m_mapGestureEvent.find(type) == m_mapGestureEvent.end())
			{
				switch (type)
				{
				case se::device::GT_TAP:
					m_mapGestureEvent[type] = new CGestureTap();
					break;
				case se::device::GT_PAN:
					m_mapGestureEvent[type] = new CGesturePan();
					break;
				case se::device::GT_PINCH:
					m_mapGestureEvent[type] = new CGesturePinch();
					break;								
				default:
					m_mapGestureEvent[type] = new CGestureTap();
					break;
				}
			}
			m_mapGestureEvent[type]->SubscribeCallback(callback, obj);
		}

		void CEventManager::UnRegisterGestureCallback(EGestureType type, GestureCallback callback)
		{			
			if (m_mapGestureEvent.find(type) != m_mapGestureEvent.end())
			{
				m_mapGestureEvent[type]->UnSubscribeCallback(callback);
			}
		}

	}
}