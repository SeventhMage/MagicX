#ifndef _MX_RESOURCE_I_TABLE_CONFIG_MANAGER_H_
#define _MX_RESOURCE_I_TABLE_CONFIG_MANAGER_H_

#include "IResourceManager.h"
#include "ITableConfig.h"

namespace mx
{
	namespace resource
	{
		class ITableConfigManager : public IResourceManager
		{
		public:
			virtual ~ITableConfigManager() {}
			virtual const ITableConfig *GetTableConfig(const char *filename) const = 0;
		};
	}
}

#endif