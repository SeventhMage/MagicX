#ifndef _MX_RENDER_C_GUASSIAN_HBLUR_H_
#define _MX_RENDER_C_GUASSIAN_HBLUR_H_

#include "CScreenAlignedQuad.h"

namespace mx
{
	namespace render
	{
		class CGuassianHBlur : public CScreenAlignedQuad
		{
		public:
			CGuassianHBlur(IRenderQueue *pRenderQueue);
			~CGuassianHBlur();

			virtual void Render();
		private:
			static const int MAX_SAMPLER_COUNT = 15;
			float m_kernel[MAX_SAMPLER_COUNT * 4];
		};
	}
}

#endif