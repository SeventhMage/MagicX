#ifndef _MX_RENDER_C_I_TERRAIN_TEXTURE_BUILDER_H_
#define _MX_RENDER_C_I_TERRAIN_TEXTURE_BUILDER_H_

#include "ITexture.h"

namespace mx
{
	namespace render
	{
		class ITerrainTextureGenerator
		{
		public:
			ITerrainTextureGenerator(){};
			virtual ~ITerrainTextureGenerator(){};

			virtual ITexture *GenerateTextureBit24(short *heightMap, uint hmWidth, int range,  char *imgName[], uint imgNum) = 0;			
			virtual void DestroyTexture(ITexture *texture) = 0;
		};
	}
}

#endif