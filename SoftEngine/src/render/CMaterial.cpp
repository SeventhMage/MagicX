#include "CMaterial.h"

namespace se
{
	namespace render
	{

		CMaterial::CMaterial(int id, const char *name)
			:m_Id(id)
			, m_strName(name)
		{

		}

		CMaterial::~CMaterial()
		{

		}

		void CMaterial::SetColor(const Color &color)
		{
			m_color = color;
		}

		void CMaterial::SetIllumination(const std::string &illumination)
		{
			m_strIllumination = illumination;
		}

	}
}