#ifndef _MX_OI_CRESOURCE_MANAGER_H_
#define _MX_OI_CRESOURCE_MANAGER_H_

#include "common/CSingleton.h"

namespace mx
{
	namespace io
	{
		class CResourceManager : public CSingleton<CResourceManager>
		{
		public:
			
		private:
			CResourceManager(){}
			~CResourceManager(){}
		};
	}
}

#endif