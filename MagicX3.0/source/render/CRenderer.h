/************************************************************************/
/* ��Ⱦ��ʵ��                                                           */
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
			IRenderDriver *m_pRenderDriver;			//��Ⱦ����
			IRenderList *m_pRenderList;		//��Ⱦ�б�
		};
	}
}

#endif