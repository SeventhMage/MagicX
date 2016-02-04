#include "resource/CResourceManager.h"


#include <string.h>

namespace mx
{
	namespace resource
	{


		CResourceManager::~CResourceManager()
		{
			ResourceMap::iterator it = m_mapResource.begin();
			for (; it != m_mapResource.end(); ++it)
			{
				if (it->second)
					delete it->second;
			}
			m_mapResource.clear();
		}

		IResource * CResourceManager::LoadResource(const char *filename)
		{
			IResource *pResource = NULL;
			if (m_mapResource.find(filename) != m_mapResource.end())
			{
				return m_mapResource[filename];
			}
			else
			{
				m_mapResource[filename] = CreateResource(filename);
				return m_mapResource[filename];
			}			
		}

		void CResourceManager::UnLoadResource(const char *filename)
		{
			if (m_mapResource.find(filename) != m_mapResource.end())
			{
				delete m_mapResource[filename];
				m_mapResource.erase(filename);
			}
		}
	}
}