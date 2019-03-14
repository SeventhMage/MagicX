#ifndef _MX_RENDER_C_GIOBJECT_H_
#define _MX_RENDER_C_GIOBJECT_H_

#include "CRenderObject.h"

namespace mx
{
	namespace render
	{
		class CGIObject : public CRenderObject
		{
		public:
			CGIObject(IRenderer *pRenderer);
			~CGIObject();

			virtual void SetTexture(IRenderable *pRenderable);
			virtual void Create(IRenderable *pRenderable);
		};
	}
}

#endif