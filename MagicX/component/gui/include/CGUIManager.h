#ifndef _MX_C_GUI_MANAGER_H_
#define _MX_C_GUI_MANAGER_H_

#include "common/mxDef.h"
#include "common/CSingleton.h"

namespace mx
{
	namespace gui
	{
		class CGUIManager : public CSingleton<CGUIManager>
		{
		public:
			CGUIManager();
			~CGUIManager();

			void Update(uint escapeTime);
			void Render();
		};
	}
}

#endif