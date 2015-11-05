#include <time.h>

#include "CTerrainEntity.h"
#include "IGPUBuffer.h"
#include "IRenderableObject.h"
#include "IShaderProgram.h"
#include "ITerrainTextureGenerator.h"



namespace mx
{
	namespace scene
	{
		CTerrainEntity::CTerrainEntity(render::IRenderer *renderer, uint width)
			:m_uWidth(width)
			,m_pRenderer(renderer)
			, m_pGPUBuffer(NULL)
			, m_pRenderableObject(NULL)
			, m_pTexture(NULL)
			, m_pTextureGenerator(NULL)
		{
			m_pHeightMap = new short[(width + 1) * (width + 1)];
			memset(m_pHeightMap, 0, sizeof(short) * ((width + 1) * (width + 1)));

			m_pMeshData = new float[6 * 5 * width * width];

		}
		CTerrainEntity::~CTerrainEntity()
		{
			SAFE_DEL(m_pHeightMap);
			if (m_pRenderer)
				m_pRenderer->DestroyGPUBuffer(m_pGPUBuffer);
			if (m_pTextureGenerator)
				m_pTextureGenerator->DestroyTexture(m_pTexture);
			
		}

		void CTerrainEntity::RandGenerateMesh()
		{
			RandHeightMap();
			GenerateMesh();
		}

		void CTerrainEntity::RandHeightMap()
		{
			srand(time(0));
		
			int var = m_uWidth;
			float zoom = 1.0f;
			int lefttop = 0;
			int righttop = m_uWidth;
			int leftbottom = (m_uWidth + 1) * m_uWidth;
			int rightbottom = leftbottom + m_uWidth;
		
			m_pHeightMap[lefttop] =  (short)GetRandomHeight(zoom);
			m_pHeightMap[righttop] =  (short)GetRandomHeight(zoom);
			m_pHeightMap[leftbottom] = (short)GetRandomHeight(zoom);
			m_pHeightMap[rightbottom] =  (short)GetRandomHeight(zoom);

			RandHeightMapSD(lefttop, righttop, rightbottom, leftbottom, 0.5f);
			
			FILE *file;
			fopen_s(&file, "heightMap.txt", "w");
			if (file)
			{
				for (uint i = 0; i < m_uWidth + 1; ++i)
				{
					for (uint j = 0; j < m_uWidth + 1; ++j)
						fprintf(file, "%-5hd", m_pHeightMap[i * (m_uWidth + 1) + j]);
					fputc('\n', file);
				}
				fclose(file);
			}
		}


		void CTerrainEntity::RandHeightMapSD(int lefttop, int righttop, int rightbottom, int leftbottom, float zoom)
		{
			if (righttop - lefttop <= 1)
				return;

			//short maxValue = 0;
			//short minValue = 0;

			//short range = GetMaxAndmin(maxValue, minValue, m_pHeightMap[lefttop], m_pHeightMap[righttop], m_pHeightMap[rightbottom], m_pHeightMap[leftbottom]);

			int curmid = (leftbottom - righttop) / 2 + righttop;
			m_pHeightMap[curmid] = (short)(((m_pHeightMap[lefttop] + m_pHeightMap[righttop] + m_pHeightMap[leftbottom] + m_pHeightMap[rightbottom]) / 4.0f) + GetRandomHeight(zoom));
			
			int left = lefttop + (leftbottom - lefttop) / 2;
			int top = lefttop + (righttop - lefttop) / 2;
			int right = righttop + (rightbottom - righttop) / 2;
			int bottom = leftbottom + (rightbottom - leftbottom) / 2;
			
			// range = GetMaxAndmin(maxValue, minValue, m_pHeightMap[lefttop], m_pHeightMap[curmid], m_pHeightMap[rightbottom], GetLeftHeight(curmid, left));
			m_pHeightMap[left] = (short)((m_pHeightMap[lefttop] + m_pHeightMap[curmid] + m_pHeightMap[leftbottom] + GetLeftHeight(curmid, left)) / 4 + GetRandomHeight(zoom));
			
			 //range = GetMaxAndmin(maxValue, minValue, m_pHeightMap[lefttop], m_pHeightMap[curmid], m_pHeightMap[righttop], GetLeftHeight(curmid, top));
			m_pHeightMap[top] = (short)((m_pHeightMap[lefttop] + m_pHeightMap[curmid] + m_pHeightMap[righttop] + GetTopHeight(curmid, top)) / 4 + GetRandomHeight(zoom));
			
			//range = GetMaxAndmin(maxValue, minValue, m_pHeightMap[curmid], m_pHeightMap[righttop], m_pHeightMap[rightbottom], GetLeftHeight(right, curmid));
			m_pHeightMap[right] = (short)((m_pHeightMap[curmid], m_pHeightMap[righttop] + m_pHeightMap[rightbottom] + GetRightHeight(right, curmid)) / 4 + GetRandomHeight(zoom));
			
			 //range = GetMaxAndmin(maxValue, minValue, m_pHeightMap[leftbottom], m_pHeightMap[curmid], m_pHeightMap[rightbottom], GetLeftHeight(bottom, curmid));
			m_pHeightMap[bottom] = (short)((m_pHeightMap[leftbottom] + m_pHeightMap[curmid] + m_pHeightMap[rightbottom] + GetBottomHeight(bottom, curmid)) / 4 + GetRandomHeight(zoom));

			RandHeightMapSD(lefttop, top, curmid, left, zoom * 0.5f);
			RandHeightMapSD(top, righttop, right, curmid, zoom * 0.5f);
			RandHeightMapSD(curmid, right, rightbottom, bottom, zoom * 0.5f);
			RandHeightMapSD(left, curmid, bottom, leftbottom, zoom * 0.5f);
		}

		short CTerrainEntity::GetHeight(uint x, uint y)
		{
			return m_pHeightMap[y * (m_uWidth + 1) + x];
		}

		void CTerrainEntity::GenerateMesh()
		{
			int k = 0;
			for (uint i = 0; i < m_uWidth; ++i)
			{
				for (uint j = 0; j < m_uWidth; ++j)
				{
					m_pMeshData[k++] = (float)j - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j, i);
					m_pMeshData[k++] = (float)i - m_uWidth / 2; 
					
					m_pMeshData[k++] = 1.0f * j / (m_uWidth + 1);
					m_pMeshData[k++] = 1.0f * i / (m_uWidth + 1);

					m_pMeshData[k++] = (float)j - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j, i + 1);
					m_pMeshData[k++] = (float)i + 1 - m_uWidth / 2; 

					m_pMeshData[k++] = 1.0f * j / (m_uWidth + 1);
					m_pMeshData[k++] = 1.0f * (i + 1)/ (m_uWidth + 1);

					m_pMeshData[k++] = (float)j + 1 - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j + 1, i);
					m_pMeshData[k++] = (float)i - m_uWidth / 2; 

					m_pMeshData[k++] = 1.0f * (j +1) / (m_uWidth + 1);
					m_pMeshData[k++] = 1.0f * i / (m_uWidth + 1);

					m_pMeshData[k++] = (float)j + 1 - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j + 1, i);
					m_pMeshData[k++] = (float)i - m_uWidth / 2;

					m_pMeshData[k++] = 1.0f * (j + 1) / (m_uWidth + 1);
					m_pMeshData[k++] = 1.0f * i / (m_uWidth + 1);

					m_pMeshData[k++] = (float)j - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j, i + 1);
					m_pMeshData[k++] = (float)i + 1 - m_uWidth / 2; 

					m_pMeshData[k++] = 1.0f * j / (m_uWidth + 1);
					m_pMeshData[k++] = 1.0f * (i + 1) / (m_uWidth + 1);

					m_pMeshData[k++] = (float)j + 1 - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j + 1, i + 1);
					m_pMeshData[k++] = (float)i + 1 - m_uWidth / 2; 

					m_pMeshData[k++] = 1.0f * (j + 1) / (m_uWidth + 1);
					m_pMeshData[k++] = 1.0f * (i + 1) / (m_uWidth + 1);
				}
			}

			m_pGPUBuffer = m_pRenderer->CreateGPUBuffer(5 * sizeof(float));
			if (m_pGPUBuffer)
			{
				m_pRenderableObject = m_pGPUBuffer->CreateRenderableObject();
				if (m_pRenderableObject)
				{
					render::IShaderProgram *shaderProgram = m_pRenderableObject->GetShaderProgram();
					if (shaderProgram)
					{
						shaderProgram->Attach("shader/terrain.ver", render::ST_VERTEX);
						shaderProgram->Attach("shader/terrain.frg", render::ST_FRAGMENT);
						shaderProgram->BindAttributeLocation(2, render::VAL_POSITION, render::VAL_TEXTURE0);
						shaderProgram->Link();
						int iTextureUnit = 0;
						shaderProgram->SetUniform("textureUnit0", &iTextureUnit);
					}
				}
				m_pGPUBuffer->Begin();
				m_pGPUBuffer->CreateVertexBuffer(m_pRenderableObject, m_pMeshData, sizeof(float) * (6 * 5 * m_uWidth * m_uWidth), 0, 6 * 3 * m_uWidth * m_uWidth, render::GBM_TRIANGLES, render::GBU_DYNAMIC_DRAW);
				m_pGPUBuffer->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0);
				m_pGPUBuffer->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, sizeof(float) * 3);

				m_pGPUBuffer->End();


				m_pTextureGenerator = m_pRenderer->GetTextureGenerator();
				if (m_pTextureGenerator)
				{
					char *filename[] = {"texture/grass.tga", "texture/land.tga", "texture/snow.tga"};
					
					m_pTexture = m_pTextureGenerator->GenerateTextureBit24(m_pHeightMap, m_uWidth + 1, MAX_HEIGHT, filename, 3);
					m_pRenderableObject->SetTexture(m_pTexture);
				}
			}
		}

		void CTerrainEntity::UpdateImp(int elapsedTime, const CMatrix4 &mat4ViewProj)
		{
			if (m_pRenderableObject)
			{
				render::IShaderProgram *shaderProgram = m_pRenderableObject->GetShaderProgram();
				if (shaderProgram)
				{
					shaderProgram->SetUniform("mvpMatrix", (void *)mat4ViewProj.m);
					
				}
			}
		}

		short CTerrainEntity::GetLeftHeight(uint high, uint low)
		{
			uint pos = 2 * low - high;
			if (pos / (m_uWidth + 1) == low / (m_uWidth + 1))
				return m_pHeightMap[pos];
			return m_pHeightMap[high];
		}

		short CTerrainEntity::GetTopHeight(uint high, uint low)
		{
			uint pos = 2 * low - high;
			if (pos % (m_uWidth + 1) == low % (m_uWidth + 1) && pos > 0)
				return m_pHeightMap[pos];
			return m_pHeightMap[high];
		}

		short CTerrainEntity::GetRightHeight(uint high, uint low)
		{
			uint pos = 2 * (high - low) + low;
			if (pos / (m_uWidth + 1) == low / (m_uWidth + 1))
				return m_pHeightMap[pos];
			return m_pHeightMap[low];
		}

		short CTerrainEntity::GetBottomHeight(uint high, uint low)
		{
			uint pos = 2 * (high - low) + low;
			if (pos % (m_uWidth + 1) == low % (m_uWidth + 1) && pos < (m_uWidth + 1) * (m_uWidth + 1))
				return m_pHeightMap[pos];
			return m_pHeightMap[low];
		}

		float CTerrainEntity::GetRandomHeight(float zoom)
		{
			int scale = (int)(zoom * MAX_HEIGHT);
			if (scale == 0)
				return 0;
			return  (rand() % scale - scale * 0.5f);
		}

		short CTerrainEntity::GetMaxAndmin(short &maxValue, short &minValue, short value1, short value2, short value3, short value4)
		{
			maxValue = minValue = value1;
			maxValue = max(maxValue, value2);
			maxValue = max(maxValue, value3);
			maxValue = max(maxValue, value4);

			minValue = min(minValue, value2);
			minValue = min(minValue, value3);
			minValue = min(minValue, value4);

			return maxValue - minValue;
		}

		float CTerrainEntity::GetRandomHeight(short base, short range)
		{
			return float (rand() % range + base);
		}


	}
		
}