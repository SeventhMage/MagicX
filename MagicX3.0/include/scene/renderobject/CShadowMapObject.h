/************************************************************************/
/* “ı”∞Õº                                                               */
/************************************************************************/

#ifndef _MX_SCENE_C_SHADOW_MAP_OBJECT_H_
#define _MX_SCENE_C_SHADOW_MAP_OBJECT_H_

#include "CRenderObject.h"

namespace mx
{
	namespace scene
	{
		class CShadowMapObject : public CRenderObject
		{
		public:
			CShadowMapObject();
			virtual ~CShadowMapObject();

			virtual void Create(IRenderable *pRenderable);
		};
	}
}

#endif