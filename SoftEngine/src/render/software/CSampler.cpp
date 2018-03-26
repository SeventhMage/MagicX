#include "CSampler.h"

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

		Color CSampler::GetColor(ITexture *pTexture, math::CVector2 texCoord)
		{
			Color resultColor(1, 1, 0, 0);
			return resultColor;
		}

		Color CSampler::GetColor(uint texUnit, math::CVector2 texCoord)
		{
			Color resultColor(1, 1, 0, 0);
			return resultColor;
		}

	}
}