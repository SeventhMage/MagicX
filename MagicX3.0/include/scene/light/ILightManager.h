/************************************************************************/
/* 光源管理类接口                                                       */
/************************************************************************/

#ifndef _MX_SCENE_I_LIGHT_MANAGER_H_
#define _MX_SCENE_I_LIGHT_MANAGER_H_

#include "ILight.h"
#include "math/CVector3.h"

namespace mx
{
	namespace scene
	{
		class ILightManager
		{
		public:
			virtual ~ILightManager(){}

			virtual ILight *CreateLight(ELightType lightType, const math::CVector3 &pos, const math::CVector3 &color) = 0;
		};
	}
}

#endif
