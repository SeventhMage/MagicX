#include "scene/light/CDirectionalLight.h"

#include <string.h>

namespace mx
{
	namespace scene
	{
		CDirectionalLight::CDirectionalLight(float color[3], const math::CVector3 &direction)
			: m_vDirection(direction)
		{
			memcpy(m_fColor, color, sizeof(m_fColor));
		}
		CDirectionalLight::~CDirectionalLight()
		{
		}
		void CDirectionalLight::SetColor(float fColor[3])
		{
			memcpy(m_fColor, fColor, sizeof(m_fColor));
		}
		float * CDirectionalLight::GetColor()
		{
			return m_fColor;
		}
	}
}