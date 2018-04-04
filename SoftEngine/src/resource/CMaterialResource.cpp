#include "CMaterialResource.h"
#include "base/base.h"

#include <fstream>


namespace se
{
	namespace resource
	{

		CMaterialResource::CMaterialResource(const char *filename)
		{
			std::ifstream in(filename);
			if (in.is_open())
			{
				char buf[512];
				while (ReadLine(in, buf, 512))
				{
					std::string str(buf);
					StringArray attValue = base::Split(str, "=");
					if (attValue.size() >= 2)
					{
						std::string attr = attValue[0];
						std::string value = attValue[1];
						EMaterialResAttr id = GetAttrID(attr);
		
						AttrValue attValue = { id, value };
						m_attrValue.push_back(attValue);
						
					}
				}
				in.close();
			}
			else
			{
				LogPrint("Can't open resource:%s\n", filename);
			}
		}

		CMaterialResource::~CMaterialResource()
		{

		}

		std::string CMaterialResource::GetValueByIdx(uint index)
		{
			if (index >= 0 && index < m_attrValue.size())
			{
				return m_attrValue[index].value;
			}
			return "";
		}

		std::string CMaterialResource::GetValue(EMaterialResAttr attr)
		{
			for (size_t i = 0; i < m_attrValue.size(); ++i)
			{
				if (m_attrValue[i].attr== attr)
				{
					return m_attrValue[i].value;
				}
			}
			return "";
		}

		bool CMaterialResource::ReadLine(std::ifstream &in, char *out, int size)
		{
			while (!in.eof())
			{
				in.getline(out, size);

				int i = 0;
				for (; i < size; ++i)
				{
					if (out[i] == 0)
						break;
					if (isspace(out[i]))
						continue;
					if (out[i] == '#')
						break;
					break;
				}
				if (isspace(out[i]) || out[i] == '#' || out[i] == 0)
					continue;
				return true;
			}
			return false;
		}

		se::resource::EMaterialResAttr CMaterialResource::GetAttrID(const std::string &strAttr)
		{
			for (int i = 0; i < MRA_COUNT; ++i)
			{
				if (strAttr == GetMSAttribute[i].attrName)
				{
					return EMaterialResAttr(i);
				}
			}
			return MRA_UNVALID;
		}

	}
}