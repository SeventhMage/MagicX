/************************************************************************/
/* “ı”∞Õº                                                               */
/************************************************************************/

#ifndef _MX_RENDER_C_SHADOW_MAP_OBJECT_H_
#define _MX_RENDER_C_SHADOW_MAP_OBJECT_H_

#include "CRenderObject.h"

namespace mx
{
	namespace render
	{
		class CShadowMapObject : public CRenderObject
		{
		public:
			CShadowMapObject();
			virtual ~CShadowMapObject();

			virtual void Create(IRenderable *pRenderable);
			virtual void SetTexture(IRenderable *pRenderable);
		};
	}
}

#endif