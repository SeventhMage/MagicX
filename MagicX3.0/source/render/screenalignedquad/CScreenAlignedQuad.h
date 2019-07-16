#ifndef _MX_C_RENDER_ALIGNED_QUAD_H_
#define _MX_C_RENDER_ALIGNED_QUAD_H_

#include "render/IRenderable.h"
#include "render/IRenderQueue.h"

namespace mx
{
	namespace render
	{
		class CScreenAlignedQuad
		{
		public:
			CScreenAlignedQuad(IRenderQueue *pRenderQueue);
			virtual ~CScreenAlignedQuad();
			virtual void Render();
		protected:
			render::IRenderable *m_pRenderable;
			ITexture *m_pRandNumTex;
		};
	}
}

#endif