#ifndef _MX_RESOURCE_C_TABLE_CONFIG_H_
#define _MX_RESOURCE_C_TABLE_CONFIG_H_

#include "resource/ITableConfig.h"
#include "rapidxml.hpp"

#include <string>

namespace mx
{
	namespace resource
	{
		class CTableConfig : public ITableConfig
		{
		public:
			CTableConfig(const char *filename);
			~CTableConfig();
			virtual std::string GetRecord(int id, const char *fieldName);
		private:
			char *m_pBuffer;
			rapidxml::xml_document<> m_doc;
			std::string m_fileName;
		};
	}
}

#endif