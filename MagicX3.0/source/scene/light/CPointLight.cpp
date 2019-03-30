#include "scene/light/CPointLight.h"
#include <string.h>

namespace mx
{
	namespace scene
	{
		CPointLight::CPointLight(float fColor[3])
		{
			memcpy(m_fColor, fColor, 3 * sizeof(float));
		}

		CPointLight::~CPointLight()
		{

		}

		void CPointLight::SetColor(float fColor[3])
		{
			memcpy(m_fColor, fColor, 3 * sizeof(float));
		}

		void CPointLight::SetPosition(const math::CVector3 &position)
		{
			m_vPosition = position;
		}

	}
}