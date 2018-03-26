#ifndef _SE_RENDER_C_SAMPLER_H_
#define _SE_RENDER_C_SAMPLER_H_

#include "render/ISampler.h"

namespace se
{
	namespace render
	{
		class CSampler : public ISampler
		{
		public:
			CSampler();
			virtual ~CSampler();

			virtual Color GetColor(ITexture *pTexture, math::CVector2 texCoord);
			virtual Color GetColor(uint texUnit, math::CVector2 texCoord);
		};
	}
}

#endif