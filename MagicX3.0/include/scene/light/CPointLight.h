/************************************************************************/
/* 点光源模型                                                           */
/************************************************************************/

#ifndef _MX_SCENE_C_POINT_LIGHT_H_
#define _MX_SCENE_C_POINT_LIGHT_H_

#include "ILight.h"

namespace mx
{
	namespace scene
	{
		class CPointLight : public ILight
		{
		public:
			CPointLight();
			virtual ~CPointLight();
		};
	}
}

#endif