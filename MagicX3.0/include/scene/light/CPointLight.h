/************************************************************************/
/* 点光源模型                                                           */
/************************************************************************/

#ifndef _MX_SCENE_C_POINT_LIGHT_H_
#define _MX_SCENE_C_POINT_LIGHT_H_

#include "ILight.h"
#include "math/CVector3.h"

namespace mx
{
	namespace scene
	{
		class CPointLight : public ILight
		{
		public:
			CPointLight(float fColor[3]);
			virtual ~CPointLight();

			virtual ELightType GetLightType() { return LT_POINT; }
			virtual void SetColor(float fColor[3]);
			virtual float *GetColor() { return m_fColor; }

			void SetPosition(const math::CVector3 &position);
			const math::CVector3 &GetPosition() { return m_vPosition; }
		private:
			math::CVector3 m_vPosition;
			float m_fColor[3];
		};

	}
}

#endif