#ifndef _RESOURCE_C_RESOURCE_MANAGER_H_
#define _RESOURCE_C_RESOURCE_MANAGER_H_

#include "resource/IResourceManager.h"

namespace mx
{
	class CResourceManager : public IResourceManager
	{
	public:
		CResourceManager();
		~CResourceManager();
	};
}

#endif