/************************************************************************/
/* ‰÷»æ∆˜ µœ÷                                                           */
/************************************************************************/
#ifndef _MX_RENDER_C_RENDERER_H_
#define _MX_RENDER_C_RENDERER_H_

#include "render/IRenderer.h"

namespace mx
{
	namespace render
	{
		class CRenderer : public IRenderer
		{
		public:
			CRenderer(ERenderDriverType type);
			virtual ~CRenderer();
			
			virtual IRenderDriver *GetRenderDriver() { return m_pRenderDriver; }
			virtual void Render();
		private:
			IRenderDriver *m_pRenderDriver;
		};
	}
}

#endif