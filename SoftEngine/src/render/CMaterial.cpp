#include "CMaterial.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{

		CMaterial::CMaterial(uint id, const char *name)
			:m_Id(id)
			, m_strName(name)
			, m_shaderProgramId(0)
			, m_ambientCoefficient(0)
			, m_diffuseCoefficient(0)
			, m_specularCoefficient(0)
			, m_specularityCoefficient(0)
		{
			m_shaderProgramId = CSoftEngine::GetRenderer()->CreateShaderProgram();
		}

		CMaterial::~CMaterial()
		{
			CSoftEngine::GetRenderer()->DestroyShaderProgram(m_shaderProgramId);
		}

		void CMaterial::SetColor(const Color &color)
		{
			m_color = color;
		}

		void CMaterial::SetIllumination(const std::string &illumination)
		{
			m_strIllumination = illumination;
		}

		IShaderProgram * CMaterial::GetShaderProgram() const
		{
			return CSoftEngine::GetRenderer()->GetShaderProgram(m_shaderProgramId);
		}

	}
}