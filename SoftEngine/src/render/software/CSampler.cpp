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
			static Color resultColor;
			ubyte *pTextureData = pTexture->GetData();
			int textureWidth = pTexture->GetWidth();
			
			float inv = 1.f / 255;
			uint x = (uint)texCoord.x;
			uint y = (uint)texCoord.y;
			
			return GetColor(pTexture, x, y);
		}

		Color CSampler::GetColor(uint texUnit, const math::CVector2 &texCoord)
		{
			ITexture *pTexture = CSoftEngine::GetTextureManager()->GetTexture(texUnit);
			return GetColor(pTexture, texCoord);
		}

		se::render::Color CSampler::GetColor(ITexture *pTexture, uint x, uint y)
		{
			static Color resultColor;
			ubyte *pTextureData = pTexture->GetData();
			int textureWidth = pTexture->GetWidth();

			float inv = 1.f / 255;
			ubyte *temp = pTextureData + y * textureWidth * 3 + x * 3;
			resultColor.a = 1.f;
			resultColor.b = *(temp)* inv;
			resultColor.g = *(temp + 1) * inv;
			resultColor.r = *(temp + 2) * inv;

			return resultColor;
		}

		const Color & CSampler::GetColor(ubyte *texData, uint texWidth, uint x, uint y)
		{
			static Color resultColor;

			float inv = 1.f / 255;
			ubyte *temp = texData + y * texWidth * 3 + x * 3;
			resultColor.a = 1.f;
			resultColor.b = *(temp)* inv;
			resultColor.g = *(temp + 1) * inv;
			resultColor.r = *(temp + 2) * inv;

			return resultColor;
		}

	}
}