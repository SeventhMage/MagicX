#ifndef _MX_RESOURCE_CRESROUCEMANAGER_H_
#define _MX_RESOURCE_CRESROUCEMANAGER_H_

#include "core/CSingleton.h"
#include "IResourceLoader.h"
#include "IResource.h"

#include <map>
#include <string>

namespace mx
{
	namespace resource
	{
		class CResourceManager
		{
		public:
			typedef std::map<std::string, IResource *> ResourceMap;
			CResourceManager(){}
			virtual ~CResourceManager();						

			IResource *LoadResource(const char *filename);
			void UnLoadResource(const char *filename);

		protected:
			virtual IResource *CreateResource(const char *filename){ return 0; }
		protected:
			ResourceMap m_mapResource;
		};
	}
}

#endif