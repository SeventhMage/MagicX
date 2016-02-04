#ifndef _MX_RESOURCE_CLOADERMANAGER_H_
#define _MX_RESOURCE_CLOADERMANAGER_H_

#include "core/CSingleton.h"
#include "IResourceLoader.h"

namespace mx
{
	namespace resource
	{
		class CLoaderManager : public CSingleton<CLoaderManager>
		{
		public:
			IResourceLoader *CreateLoader(const char *extName);
			void DestroyLoader(IResourceLoader *loader);
		};
	}
}

#endif