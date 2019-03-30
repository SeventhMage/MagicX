/************************************************************************/
/* 方向光                                                               */
/************************************************************************/

#ifndef _MX_SCENE_C_DIRECTIONAL_LIGHT_H_
#define _MX_SCENE_C_DIRECTIONAL_LIGHT_H_

#include "ILight.h"
#include "math/CVector3.h"

namespace mx
{
	namespace scene
	{
		class CDirectionalLight : public ILight
		{
		public:
			CDirectionalLight(float color[3], const math::CVector3 &direction = math::CVector3(0, 0, -1.f));
			virtual ~CDirectionalLight();

			virtual ELightType GetLightType() { return LT_DIRECTIONAL; }
			//光的颜色
			virtual void SetColor(float fColor[3]);
			virtual float *GetColor();
			void SetDirection(const math::CVector3 &dir) { m_vDirection = dir; }
			const math::CVector3 &GetDirection() { return m_vDirection; }
		private:
			float m_fColor[3];
			math::CVector3 m_vDirection;
		};
	}
}

#endif