#include "CPointLight.h"
#include <string.h>

namespace se
{
	namespace scene
	{
		CPointLight::CPointLight(float fColor[4])
		{
			memcpy(m_fColor, fColor, 4 * sizeof(float));
		}

		CPointLight::~CPointLight()
		{

		}

		void CPointLight::SetColor(float fColor[4])
		{
			memcpy(m_fColor, fColor, 4 * sizeof(float));
		}

		void CPointLight::SetPosition(const math::CVector3 &position)
		{
			m_vPosition = position;
		}

	}
}