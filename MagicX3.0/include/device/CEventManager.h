#ifndef _MX_DEVICE_C_EVENT_MANAGER_H_
#define _MX_DEVICE_C_EVENT_MANAGER_H_

#include "base/CSingleton.h"
#include "device/IKeyEvent.h"
#include "device/IDevice.h"
#include "mxType.h"

namespace mx
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
		private:
			CEventManager();
			~CEventManager();
			IKeyEvent *m_pKeyEvent;
			IDevice *m_pDevice;
		};
	}
}

#endif
