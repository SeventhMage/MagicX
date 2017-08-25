#ifndef _MX_DEVICE_C_EVENT_MANAGER_H_
#define _MX_DEVICE_C_EVENT_MANAGER_H_

#include "base/CSingleton.h"
#include "device/IKeyEvent.h"
#include "device/IDevice.h"
#include "base/seType.h"
#include "IGestureEvent.h"
#include "EEvent.h"

#include <map>

namespace se
{
	namespace device
	{
		class CEventManager : public base::CSingleton<CEventManager>
		{
		public:
			friend base::CSingleton<CEventManager>;
			IKeyEvent *GetKeyEvent() { return m_pKeyEvent; }
			void SetDevice(IDevice *device){ m_pDevice = device; }
			void OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight);					
						
			void RegisterGestureCallback(EGestureType type, GestureCallback callback, void *obj);			
			void UnRegisterGestureCallback(EGestureType type, GestureCallback callback);
		private:
			CEventManager();
			~CEventManager();			
			IDevice *m_pDevice;
			IKeyEvent *m_pKeyEvent;
			std::map<EGestureType, IGestureEvent *> m_mapGestureEvent;
		};
	}
}

#endif
