#include "COpenGLTerrainTextureGenerator.h"
#include "CTGA.h"

namespace mx
{
	namespace render
	{
		COpenGLTerrainTextureGenerator::COpenGLTerrainTextureGenerator(float mixRate /* = 0.2f */)
			:m_fMixRate(mixRate)
		{

		}

		COpenGLTerrainTextureGenerator::~COpenGLTerrainTextureGenerator()
		{
			for (uint i = 0; i < m_vecTexture.size(); ++i)
			{
				SAFE_DEL(m_vecTexture[i]);
			}
		}

		ITexture * COpenGLTerrainTextureGenerator::GenerateTextureBit24(short *heightMap, uint hmWidth, int range, char *imgName[], uint imgNum)
		{
			float width = range / (imgNum - (imgNum - 1) * m_fMixRate);
			float mixRange = m_fMixRate * width;

			CTGA *tags = new CTGA[imgNum];

			for (uint i = 0; i < imgNum; ++i)
			{
				tags[i].ReadTGABits(imgName[i]);
			}

			SHeightRange *heightRange = new SHeightRange[imgNum];

			for (int i = 0; i < imgNum; ++i)
			{
				heightRange[i].minRange = i * (width - m_fMixRate * width);
				heightRange[i].maxRange = heightRange[i].minRange + width;
				heightRange[i].leftMixPos = i == 0 ? 0 : heightRange[i].minRange + mixRange;
				heightRange[i].rightMixPos = i == imgNum - 1 ? heightRange[i].rightMixPos : heightRange[i].maxRange - mixRange;
			}

			Byte *destData = new Byte[hmWidth * hmWidth * 8 * 3];
			uint k = 0;
			for (uint i = 0; i < hmWidth; ++i)
			{
				for (uint j = 0; j < hmWidth; ++j)
				{
					short height = heightMap[i * hmWidth + j];
					for (int p = 0; p < imgNum; ++p)
					{
						if (height >= heightRange[i].minRange && height <= heightRange[i].maxRange)
						{
							float rate = 1.0f;
							if (height < heightRange[i].leftMixPos)							
								rate = (height - heightRange[i].minRange) / width;															
							else if (height > heightRange[i].rightMixPos)							
								rate = (heightRange[i].maxRange - height) / width;								
							
							destData[k] = (tags[p].GetData()[(i * 3 * 8 * tags[p].GetWidth()) % tags[p].GetWidth() + j % tags[p].GetWidth()]) * rate;
							destData[k + 1] = (tags[p].GetData()[(i * 3 * 8 * tags[p].GetWidth()) % tags[p].GetWidth() + (j + 1) % tags[p].GetWidth()]) * rate;
							destData[k + 2] = (tags[p].GetData()[(i * 3 * 8 * tags[p].GetWidth()) % tags[p].GetWidth() + (j + 2) % tags[p].GetWidth()]) * rate;
						}
					}
					++k;
				}
			}

			COpenGLTexture *texture = new COpenGLTexture();
			if (texture->Create2DBit24(destData, hmWidth, hmWidth))
			{
				m_vecTexture.push_back(texture);
				return texture;
			}
			SAFE_DEL_ARRAY(destData);
			SAFE_DEL_ARRAY(heightRange);
			return NULL;
		}

		void COpenGLTerrainTextureGenerator::DestroyTexture(ITexture *texture)
		{
			for (uint i = 0; i < m_vecTexture.size(); ++i)
			{
				if (m_vecTexture[i] == texture)
				{
					m_vecTexture.erase(i + m_vecTexture.begin());
					SAFE_DEL(texture);
				}
			}
		}

	}
}