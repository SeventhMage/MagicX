/************************************************************************/
/* 反射对象，与网格数据结合构成可渲染对像                               */
/************************************************************************/
#ifndef _MX_RENDER_C_REFLECT_OBJECT_H_
#define _MX_RENDER_C_REFLECT_OBJECT_H_

#include "CRenderObject.h"

namespace mx
{
	namespace render
	{		
		class CReflectObject : public CRenderObject
		{
		public:
			CReflectObject(IRenderer *pRenderer);
			~CReflectObject();						

			virtual void SetTexture(IRenderable *pRenderable);
			virtual void Create(IRenderable *pRenderable);
		private:
			
		};
	}
}

#endif