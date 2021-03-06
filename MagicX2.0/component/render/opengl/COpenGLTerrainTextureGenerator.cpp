#include "COpenGLTerrainTextureGenerator.h"
#include "CTGA.h"
#include "mxDef.h"

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

			CTGA *tgas = new CTGA[imgNum];

			for (uint i = 0; i < imgNum; ++i)
			{
				tgas[i].ReadTGABits(imgName[i]);
			}

			SHeightRange *heightRange = new SHeightRange[imgNum];

			for (uint i = 0; i < imgNum; ++i)
			{
				heightRange[i].minRange = i * (width - m_fMixRate * width);
				heightRange[i].maxRange = heightRange[i].minRange + width;
				heightRange[i].leftMixPos = i == 0 ? 0 : heightRange[i].minRange + mixRange;
				heightRange[i].rightMixPos = i == imgNum - 1 ? heightRange[i].maxRange : heightRange[i].maxRange - mixRange;
			}

			for (uint i = 0; i < imgNum; ++i)
			{
				heightRange[i].minRange -= 0.5f * range;
				heightRange[i].maxRange -= 0.5f * range;
				heightRange[i].leftMixPos -= 0.5f * range;
				heightRange[i].rightMixPos -= 0.5f * range;
			}

			uint heightMapSize = (hmWidth - 1) * (hmWidth - 1) * 3;
			byte *destData = new byte[heightMapSize];
			memset(destData, 0, sizeof(byte) * heightMapSize);
			uint k = 0;
			for (uint i = 0; i < (hmWidth - 1); ++i)
			{
				for (uint j = 0; j < (hmWidth - 1); ++j)
				{
					short height = heightMap[i * (hmWidth - 1) + j];
					for (uint p = 0; p < imgNum; ++p)
					{
						if (height >= heightRange[p].minRange && height <= heightRange[p].maxRange)
						{
							float rate = 1.0f;
							if (height < heightRange[p].leftMixPos)
								rate = (height - heightRange[p].minRange) / (heightRange[p].leftMixPos - heightRange[p].minRange);
							else if (height > heightRange[p].rightMixPos)
								rate = (heightRange[p].maxRange - height) / (heightRange[p].maxRange - heightRange[p].rightMixPos);
							
							uint pos = /*i * tgas[p].GetWidth() * 3 + j * 3*/ ((i % (tgas[p].GetWidth() * 3)) * 3 * tgas[p].GetWidth()) + (j * 3) % (tgas[p].GetWidth() * 3);
							
							destData[k] += (tgas[p].GetData()[pos++]) * rate;						
							destData[k+1] += (tgas[p].GetData()[pos++]) * rate;							
							destData[k+2] += (tgas[p].GetData()[pos++]) * rate;
						}
					}
					k += 3;
				}
			}
// 			for (uint i = 0; i < tgas[1].GetImageSize(); ++i)
// 			{
// 				//printf("%-5d%-5d", destData[i], tgas[1].GetData()[i]);
// 				if (abs(destData[i] != tgas[1].GetData()[i]))
// 					getchar();
// 			}
			COpenGLTexture *texture = new COpenGLTexture();
			if (texture->Create2DBit24(destData, hmWidth - 1, hmWidth - 1))
			//if (texture->Create2D("texture/1.tga"))
			{
				m_vecTexture.push_back(texture);
			}
			else
			{
				SAFE_DEL(texture);
			}
			CTGA tgaWrite;
			
			tgaWrite.WriteTGAFile("terrainmap.tga", (char *)destData, hmWidth - 1, hmWidth - 1);
			SAFE_DEL_ARRAY(destData);
			SAFE_DEL_ARRAY(heightRange);
			return texture;
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