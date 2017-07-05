#include "CMaterialResource.h"

namespace se
{
	namespace resource
	{

		CMaterialResource::CMaterialResource(const char *filename)
		{

		}

		CMaterialResource::~CMaterialResource()
		{

		}

		std::string CMaterialResource::GetValueByIdx(int index)
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

	}
}