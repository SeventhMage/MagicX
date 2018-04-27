#ifndef _DEVICE_C_EVENT_MANAGER_H_
#define _DEVICE_C_EVENT_MANAGER_H_

#include "base/CSingleton.h"
#include "device/IDevice.h"
#include "IEvent.h"

namespace mx
{
	class CEventManager : public CSingleton<CEventManager>
	{
	public:
		friend CSingleton<CEventManager>;

		IEvent *GetEvent(EEventType et) { return m_eventList[et]; }
		void RegisterEvent(IEvent *pEvnet);
		void SetDevice(IDevice *device){ m_pDevice = device; }
		void OnSize(int x, int y, int widht, int height);

	private:
		CEventManager();
		~CEventManager();			
		IDevice *m_pDevice;
		IEvent *m_eventList[ET_NUM];
		
	};
	
}

#endif
