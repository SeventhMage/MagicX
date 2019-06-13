#ifndef _MX_RENDER_C_SCREEN_DIRECT_LIGHT_MAP_H_
#define _MX_RENDER_C_SCREEN_DIRECT_LIGHT_MAP_H_

#include "CScreenAlignedQuad.h"

namespace mx
{
	namespace render
	{
		class CDirectLightMap : public CScreenAlignedQuad
		{
		public:
			CDirectLightMap(IRenderQueue *pRenderQueue);
			~CDirectLightMap();

			virtual void Render();


		};
	}
}

#endif