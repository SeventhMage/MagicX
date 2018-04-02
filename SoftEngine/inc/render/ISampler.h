#ifndef _SE_RENDER_I_SAMPLER_H_
#define _SE_RENDER_I_SAMPLER_H_

#include "SColor.h"
#include "ITexture.h"
#include "math/CVector2.h"

namespace se
{
	namespace render
	{
		class ISampler
		{
		public:
			virtual ~ISampler(){}

			virtual Color GetColor(ITexture *pTexture, const math::CVector2 &texCoord) = 0;
			virtual Color GetColor(uint texUnit, const math::CVector2 &texCoord) = 0;
			virtual Color GetColor(ITexture *pTexture, uint x, uint y) = 0;
			virtual const Color &GetColor(ubyte *texData, uint texWidth, uint x, uint y) = 0;
		};
	}
}

#endif