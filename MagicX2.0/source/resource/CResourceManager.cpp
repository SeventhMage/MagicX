#include "resource/CResourceManager.h"
#include "resource/CPLXLoader.h"

#include <string.h>

namespace mx
{
	namespace resource
	{


		IMesh * CResourceManager::LoadResource(const char *filename)
		{
			IMesh *pMesh = NULL;
			const char *extPos = strrchr(filename, '.');
			if (extPos)
			{
				if (0 == strcmp(extPos, ".plg") || 0 == strcmp(extPos, ".plx"))
				{					
					CPLXLoader loader;
					pMesh = loader.LoadResource(filename);
				}
			}
			return pMesh;
		}

		void CResourceManager::UnLoadResource(IMesh *pMesh)
		{
			if (pMesh)
			{
				delete pMesh;
				pMesh = NULL;
			}
		}

	}
}