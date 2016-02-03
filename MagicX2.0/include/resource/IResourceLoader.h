#ifndef _MX_RESOURCE_IRESOURCELOADER_H_
#define _MX_RESOURCE_IRESOURCELOADER_H_

#include "IResource.h"

namespace mx
{
	namespace resource
	{
		class IResourceLoader
		{
		public:
			IResourceLoader(){}
			virtual ~IResourceLoader(){}	

			virtual bool LoadResource(const char *filename, IResource *pResource) = 0;
		};
	}
}

#endif