#ifndef _MX_RENDER_C_SCREEN_ALIGNED_QUAD_MANAGER_H_
#define _MX_RENDER_C_SCREEN_ALIGNED_QUAD_MANAGER_H_

#include "CScreenAlignedQuad.h"
#include "render/IScreenAlignedQuadManager.h"

namespace mx
{
	namespace render
	{
		class CScreenAlignedQuadManager : public IScreenAlignedQuadManager
		{
		public:
			CScreenAlignedQuadManager();
			~CScreenAlignedQuadManager();

			virtual void Render();

			virtual void  CreateScreenAlignedQuad(const char *name, IRenderQueue *pRenderQuque);
		private:
			std::vector<CScreenAlignedQuad *> m_ScreenAlignedQuadArray;
		};
	}
}

#endif