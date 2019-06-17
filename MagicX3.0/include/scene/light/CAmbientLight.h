/************************************************************************/
/* »·¾³¹â                                                               */
/************************************************************************/

#ifndef _MX_SCENE_C_AMBIENT_LIGHT_H_
#define _MX_SCENE_C_AMBIENT_LIGHT_H_

#include "ILight.h"

namespace mx
{
	namespace scene
	{
		class CAmbientLight : public ILight
		{
		public:
			CAmbientLight(float lightColor[3])
			{
				memcpy(m_fColor, lightColor, sizeof(m_fColor));
			}
			virtual ~CAmbientLight(){}
			virtual ELightType GetLightType() { return LT_AMBIENT; }
			virtual void SetColor(float fColor[3]) { memcpy(m_fColor, fColor, sizeof(m_fColor)); }
			virtual float *GetColor() { return m_fColor; }
		private:
			float m_fColor[3];
		};
	}
}

#endif