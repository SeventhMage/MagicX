/************************************************************************/
/* 渲染器实现                                                           */
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
			CRenderer(IRenderDriver *pRenderDriver);
			virtual ~CRenderer();
			
			virtual IRenderDriver *GetRenderDriver() { return m_pRenderDriver; }
			virtual IRenderable *CreateRenderable();
			virtual void DestroyRenderable(IRenderable *pRenderable);
			virtual void Render();
		protected:
			IRenderDriver *m_pRenderDriver;			//渲染驱动
			IRenderList *m_pRenderList;		//渲染列表
		};
	}
}

#endif