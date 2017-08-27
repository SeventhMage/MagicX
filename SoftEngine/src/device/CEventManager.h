#ifndef _MX_DEVICE_C_EVENT_MANAGER_H_
#define _MX_DEVICE_C_EVENT_MANAGER_H_

#include "device/IEventManager.h"
#include "base/CSingleton.h"

#include <map>

namespace se
{
	namespace device
	{
		class CEventManager : public IEventManager, public base::CSingleton<CEventManager>
		{
		public:
			friend base::CSingleton<CEventManager>;
			virtual IKeyEvent *GetKeyEvent() { return m_pKeyEvent; }
			virtual void SetDevice(IDevice *device){ m_pDevice = device; }
			virtual void OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight);
						
            virtual void OnTouchBegin(int pointID, int x, int y, uint classID, uint touchNum);
            virtual void OnTouchEnd(int pointID, int x, int y, uint classID, uint touchNum);
            virtual void OnTouchMove(int pointID, int x, int y, uint classID, uint touchNum);
			virtual void RegisterGestureCallback(EGestureType type, GestureCallback callback);
			virtual void UnRegisterGestureCallback(EGestureType type, GestureCallback callback);
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
