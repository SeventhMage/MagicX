/************************************************************************/
/* 资源管理器                                                           */
/************************************************************************/

#ifndef _MX_RESOURCE_C_MANAGER_H_
#define _MX_RESOURCE_C_MANAGER_H_

#include "resource/IResourceManager.h"

namespace mx
{
	namespace resource
	{
		class CResourceManager : public IResourceManager
		{
		public:
			CResourceManager();
			virtual ~CResourceManager();

			virtual IResource *LoadResource(const char *filename);
		};
	}
}

#endif