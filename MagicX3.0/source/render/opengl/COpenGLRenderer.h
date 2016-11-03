/************************************************************************/
/* ‰÷»æ∆˜                                                               */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_RENDERER_H_
#define _MX_RENDER_C_OPENGL_RENDERER_H_

#include "render/IRenderer.h"
#include "render/IRenderList.h"

namespace mx
{
	namespace render
	{
		class COpenGLRenderer : public IRenderer
		{
		public:
			COpenGLRenderer();
			virtual ~COpenGLRenderer();

			virtual IRenderDriver *GetRenderDriver() { return m_pRenderDriver; }
			virtual void Render(IRenderable *pRenderable);
		private:
			IRenderDriver *m_pRenderDriver;		//‰÷»æ«˝∂Ø
			IRenderList *m_pRenderQueue;		//‰÷»æ∂”¡–

		};
	}
}

#endif