#ifndef _MX_RENDER_C_OPENGL_TERRAIN_TEXTURE_BUILDER_H_
#define _MX_RENDER_C_OPENGL_TERRAIN_TEXTURE_BUILDER_H_

#include <vector>

#include "../../Include/ITerrainTextureGenerator.h"
#include "COpenGLTexture.h"

namespace mx
{
	namespace render
	{
		struct SHeightRange
		{
			float minRange;
			float maxRange;
			float leftMixPos;
			float rightMixPos;
		};

		class COpenGLTerrainTextureGenerator : public ITerrainTextureGenerator
		{
		public:
			COpenGLTerrainTextureGenerator(float mixRate = 0.2f);
			virtual ~COpenGLTerrainTextureGenerator();

			virtual ITexture *GenerateTextureBit24(short *heightMap, uint hmWidth, int range, char *imgName[], uint imgNum);
			virtual void DestroyTexture(ITexture *texture);
		private:
			float m_fMixRate;
			std::vector<COpenGLTexture *> m_vecTexture;
		};
	}
}

#endif