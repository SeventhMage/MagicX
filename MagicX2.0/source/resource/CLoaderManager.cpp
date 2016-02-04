#include "resource/CLoaderManager.h"
#include "resource/CPLXLoader.h"
#include "mxDef.h"

#include <string.h>

namespace mx
{
	namespace resource
	{
		IResourceLoader * CLoaderManager::CreateLoader(const char *extName)
		{
			IResourceLoader *pLoader = NULL;
			if (0 == strcmp(extName, ".plg") || 0 == strcmp(extName, ".plx"))
			{
				pLoader = new CPLXLoader();
			}
			return pLoader;
		}

		void CLoaderManager::DestroyLoader(IResourceLoader *loader)
		{
			SAFE_DEL(loader);
		}
	}
}