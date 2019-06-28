#ifndef _MX_RESOURCE_I_TABLE_CONFIG_H_
#define _MX_RESOURCE_I_TABLE_CONFIG_H_

#include "IResource.h"

#include <string>

namespace mx
{
	namespace resource
	{
		class ITableConfig : public IResource
		{
		public:
			virtual std::string GetRecord(int id, const char *fieldName) = 0;
		};
	}
}

#endif