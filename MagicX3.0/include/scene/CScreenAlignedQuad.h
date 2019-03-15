#ifndef _MX_C_SCREEN_ALIGNED_QUAD_H_
#define _MX_C_SCREEN_ALIGNED_QUAD_H_

#include "render/IRenderable.h"

namespace mx
{
	namespace scene
	{
		class CScreenAlignedQuad
		{
		public:
			CScreenAlignedQuad(int phaseid, int materialid);
			~CScreenAlignedQuad();
			void Render();
		private:
			render::IRenderable *m_pRenderable;
		};
	}
}

#endif