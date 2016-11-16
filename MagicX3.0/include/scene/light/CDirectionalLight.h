/************************************************************************/
/* ·½Ïò¹â                                                               */
/************************************************************************/

#ifndef _MX_SCENE_C_DIRECTIONAL_LIGHT_H_
#define _MX_SCENE_C_DIRECTIONAL_LIGHT_H_

#include "ILight.h"

namespace mx
{
	namespace scene
	{
		class CDirectionalLight : public ILight
		{
		public:
			CDirectionalLight();
			virtual ~CDirectionalLight();
		};
	}
}

#endif