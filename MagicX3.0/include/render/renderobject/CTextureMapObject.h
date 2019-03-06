#ifndef _MX_RENDER_C_TEXTURE_OBJECT_
#define _MX_RENDER_C_TEXTURE_OBJECT_

#include "CRenderObject.h"

namespace mx
{
	namespace render
	{
		class CTextureMapObject : public CRenderObject
		{
		public:
			CTextureMapObject(IRenderer *pRenderer);
			virtual ~CTextureMapObject();
			virtual void Create(IRenderable *pRenderable);
		};
	}
}

#endif