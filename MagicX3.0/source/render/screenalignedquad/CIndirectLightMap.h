#ifndef _MX_RENDER_C_SCREEN_INDERICT_LIGHT_MAP_H_
#define _MX_RENDER_C_SCREEN_INDIRECT_LIGHT_MAP_H_

#include "CScreenAlignedQuad.h"

namespace mx
{
	namespace render
	{
		class CIndirectLightMap : public CScreenAlignedQuad
		{
		public:
			CIndirectLightMap(IRenderQueue *pRenderQueue);
			~CIndirectLightMap();

			virtual void Render();


		};
	}
}

#endif