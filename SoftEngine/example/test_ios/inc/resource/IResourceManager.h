#ifndef _I_RESOURCE_MANAGER_H_
#define _I_RESOURCE_MANAGER_H_

#include "resource/IResource.h"

namespace se
{
	namespace resource
	{
		class IResourceManager
		{
		public:
			virtual ~IResourceManager(){}
			virtual IResource *LoadResource(const char *filename) = 0;
			virtual void ReleaseResource(IResource *pResource) = 0;
		};
	}
}

#endif