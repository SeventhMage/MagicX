/************************************************************************/
/* äÖÈ¾Æ÷                                                               */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_RENDERER_H_
#define _MX_RENDER_C_OPENGL_RENDERER_H_

#include "../CRenderer.h"
#include "render/IRenderList.h"

namespace mx
{
	namespace render
	{
		class COpenGLRenderer : public CRenderer
		{
		public:
			COpenGLRenderer();
			virtual ~COpenGLRenderer();

			virtual void Render(IRenderable *pRenderable);

		};
	}
}

#endif