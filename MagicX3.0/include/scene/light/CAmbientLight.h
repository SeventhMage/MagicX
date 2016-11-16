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
			CAmbientLight();
			virtual ~CAmbientLight();
		};
	}
}

#endif