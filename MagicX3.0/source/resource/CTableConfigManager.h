#ifndef _MX_RESOURCE_C_TABLE_CONFIG_MANAGER_H_
#define _MX_RESOURCE_C_TABLE_CONFIG_MANAGER_H_

#include "resource/ITableConfigManager.h"

#include <unordered_map>

namespace mx
{
	namespace resource
	{
		class CTableConfigManager : public ITableConfigManager
		{
		public:
			CTableConfigManager();
			~CTableConfigManager();
			virtual IResource *LoadResource(const char *filename);
			virtual void UnLoadResource(IResource *pResource);
			virtual const ITableConfig *GetTableConfig(const char *filename) const;
		private:
			std::unordered_map<std::string, ITableConfig *> m_tabelConfig;
		};
	}
}

#endif