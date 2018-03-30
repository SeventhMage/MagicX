#include "CSampler.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{		

		CSampler::CSampler()
		{

		}

		CSampler::~CSampler()
		{

		}

		Color CSampler::GetColor(ITexture *pTexture, const math::CVector2 &texCoord)
		{
			Color resultColor(1, 1, 0, 0);
			ubyte *pTextureData = pTexture->GetData();
			int textureWidth = pTexture->GetWidth();
			
			float inv = 1.f / 255;

			resultColor.a = 1.f;
			resultColor.b = *(pTextureData + uint(texCoord.y) * textureWidth * 3 + uint(texCoord.x) * 3) * inv;
			resultColor.g = *(pTextureData + uint(texCoord.y) * textureWidth * 3 + uint(texCoord.x) * 3 + 1) * inv;
			resultColor.r = *(pTextureData + uint(texCoord.y) * textureWidth * 3 + uint(texCoord.x) * 3 + 2) * inv;

			return resultColor;
		}

		Color CSampler::GetColor(uint texUnit, const math::CVector2 &texCoord)
		{
			ITexture *pTexture = CSoftEngine::GetTextureManager()->GetTexture(texUnit);
			return GetColor(pTexture, texCoord);
		}

	}
}