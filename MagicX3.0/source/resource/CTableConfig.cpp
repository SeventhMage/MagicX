#include "CTableConfig.h"
#include "mxDef.h"

#include <fstream>

namespace mx
{
	namespace resource
	{

		CTableConfig::CTableConfig(const char *filename)
			:m_fileName(filename)
		{
			std::ifstream infile(filename, std::ios::in);
			if (!infile)
			{
				return;
			}
			std::streampos pos = infile.tellg();
			infile.seekg(0, std::ios::end);
			int fileLen = infile.tellg();
			infile.seekg(0, pos);
			m_pBuffer = new char[fileLen];
			memset(m_pBuffer, 0, sizeof(char) * fileLen);
			infile.read(m_pBuffer, sizeof(char) * fileLen);
			m_doc.parse<0>(m_pBuffer);
		}

		CTableConfig::~CTableConfig()
		{
			SAFE_DEL(m_pBuffer);
		}

		std::string CTableConfig::GetRecord(int id, const char *fieldName)
		{
			rapidxml::xml_node<> *rootNode = m_doc.first_node("table");
			if (rootNode)
			{
				for (rapidxml::xml_node<> * node = rootNode->first_node("record"); node; node = node->next_sibling())
				{
					int recordid = atoi(node->first_attribute("id")->value());
					if (recordid == id)
					{
						if (node->first_attribute(fieldName))
						{
							return  node->first_attribute(fieldName)->value();
						}
					}
				}
			}
			return "";
		}

	}
}