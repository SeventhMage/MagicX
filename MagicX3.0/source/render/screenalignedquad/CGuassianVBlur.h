#ifndef _MX_RENDER_C_GUASSIAN_V_BLUR_H_
#define _MX_RENDER_C_GUASSIAN_V_BLUR_H_

#include "CScreenAlignedQuad.h"

namespace mx
{
	namespace render
	{
		class  CGuassianVBlur: public CScreenAlignedQuad
		{
		public:
			CGuassianVBlur(IRenderQueue *pRenderQueue);
			~CGuassianVBlur();

			virtual void Render();
		private:
			static const int MAX_SAMPLER_COUNT = 15;
			float m_kernel[MAX_SAMPLER_COUNT * 4];
		};
	}
}

#endif#pragma once
