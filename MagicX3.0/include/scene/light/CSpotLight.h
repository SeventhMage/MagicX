/************************************************************************/
/* ¾Û¹âµÆÄ£ÐÍ                                                           */
/************************************************************************/

#ifndef _MX_SCENE_C_SPOT_LIGHT_H_
#define _MX_SCENE_C_SPOT_LIGHT_H_

#include "ILight.h"

namespace mx
{
	namespace scene
	{
		class CSpotLight : public ILight
		{
		public:
			CSpotLight();
			virtual ~CSpotLight();

		};
	}
}

#endif