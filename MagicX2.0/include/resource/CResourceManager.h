#ifndef _MX_RESOURCE_CRESROUCEMANAGER_H_
#define _MX_RESOURCE_CRESROUCEMANAGER_H_

#include "core/CSingleton.h"
#include "IResourceLoader.h"
#include "IMesh.h"

namespace mx
{
	namespace resource
	{
		class CResourceManager : public CSingleton<CResourceManager>
		{
		public:
			CResourceManager(){}
			virtual ~CResourceManager(){}
			IMesh *LoadResource(const char *filename);
			void UnLoadResource(IMesh *pMesh);
		};
	}
}

#endif