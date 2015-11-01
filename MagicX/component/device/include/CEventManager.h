#ifndef _MX_DEVICE_C_EVENT_MANAGER_H_
#define _MX_DEVICE_C_EVENT_MANAGER_H_

#include "common/CSingleton.h"
#include "IKeyEvent.h"

namespace mx
{
	namespace device
	{
		class CEventManager : public CSingleton<CEventManager>
		{
		public:
			friend CSingleton<CEventManager>;
			IKeyEvent *GetKeyEvent() { return m_pKeyEvent; }

		private:
			CEventManager();
			~CEventManager();
			IKeyEvent *m_pKeyEvent;

		};
	}
}

#endif
