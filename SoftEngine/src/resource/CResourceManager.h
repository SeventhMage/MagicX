#ifndef _SE_C_RESOURCE_MANAGER_H_
#define _SE_C_RESOURCE_MANAGER_H_

#include "resource/IResourceManager.h"
#include "base/CSingleton.h"

namespace se
{
	namespace resource
	{
		class CResourceManager : public IResourceManager, public base::CSingleton<CResourceManager>
		{
		public:
			virtual IResource *LoadResource(const char *filename);
			virtual void ReleaseResource(IResource *pResource);
		};
	}
}

#endif