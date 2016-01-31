#ifndef _MX_RESOURCE_IRESOURCELOADER_H_
#define _MX_RESOURCE_IRESOURCELOADER_H_

#include "IMesh.h"

namespace mx
{
	namespace resource
	{
		class IResourceLoader
		{
		public:
			IResourceLoader(){}
			virtual ~IResourceLoader(){}	

			virtual IMesh *LoadResource(const char *filename) = 0;
		};
	}
}

#endif