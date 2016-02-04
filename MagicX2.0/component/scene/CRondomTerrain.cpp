#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mxDef.h"
#include "CRandomTerrain.h"
#include "render/IGPUBuffer.h"
#include "render/IRenderableObject.h"
#include "render/IShaderProgram.h"
#include "render/ITerrainTextureGenerator.h"
#include "core/CMatrix4.h"


namespace mx
{
	namespace scene
	{
		CRandomTerrain::CRandomTerrain(render::IRenderer *renderer, uint width)
			:m_uWidth(width)
			,m_pRenderer(renderer)
			, m_pGPUBuffer(NULL)
			, m_pRenderableObject(NULL)
			, m_pTexture(NULL)
			, m_pTextureGenerator(NULL)
		{
			m_pHeightMap = new short[(width + 1) * (width + 1)];
			memset(m_pHeightMap, 0, sizeof(short) * ((width + 1) * (width + 1)));
			
			m_pMeshData = new SMesh;
			m_pMeshData->uVertNum = (width + 1) * (width + 1);
			m_pMeshData->uIdsNum = (width + 1) * 2 * width;
			m_pMeshData->pVertices = new SVertex[m_pMeshData->uVertNum];
			m_pMeshData->pIndices = new uint[m_pMeshData->uIdsNum];

			memset(m_pMeshData->pIndices, 0, sizeof(uint)* m_pMeshData->uIdsNum);
		}
		CRandomTerrain::~CRandomTerrain()
		{
			SAFE_DEL(m_pHeightMap);
			if (m_pRenderer)
				m_pRenderer->DestroyGPUBuffer(m_pGPUBuffer);
			if (m_pTextureGenerator)
				m_pTextureGenerator->DestroyTexture(m_pTexture);
			SAFE_DEL_ARRAY(m_pMeshData->pVertices);
			SAFE_DEL_ARRAY(m_pMeshData->pIndices);
			SAFE_DEL(m_pMeshData)
		}

		void CRandomTerrain::RandGenerateMesh()
		{
			RandHeightMap();
			GenerateMesh();
		}

		void CRandomTerrain::RandHeightMap()
		{
			srand((uint)time(0));
		
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


		void CRandomTerrain::RandHeightMapSD(int lefttop, int righttop, int rightbottom, int leftbottom, float zoom)
		{
			if (righttop - lefttop <= 1)
				return;

			int curmid = (leftbottom - righttop) / 2 + righttop;
			m_pHeightMap[curmid] = (short)(((m_pHeightMap[lefttop] + m_pHeightMap[righttop] + m_pHeightMap[leftbottom] + m_pHeightMap[rightbottom]) / 4.0f) + GetRandomHeight(zoom));
			
			int left = lefttop + (leftbottom - lefttop) / 2;
			int top = lefttop + (righttop - lefttop) / 2;
			int right = righttop + (rightbottom - righttop) / 2;
			int bottom = leftbottom + (rightbottom - leftbottom) / 2;
			
			
			m_pHeightMap[left] = (short)((m_pHeightMap[lefttop] + m_pHeightMap[curmid] + m_pHeightMap[leftbottom] + GetLeftHeight(curmid, left)) / 4 + GetRandomHeight(zoom));
			
			
			m_pHeightMap[top] = (short)((m_pHeightMap[lefttop] + m_pHeightMap[curmid] + m_pHeightMap[righttop] + GetTopHeight(curmid, top)) / 4 + GetRandomHeight(zoom));
			
			
			m_pHeightMap[right] = (short)((m_pHeightMap[curmid], m_pHeightMap[righttop] + m_pHeightMap[rightbottom] + GetRightHeight(right, curmid)) / 4 + GetRandomHeight(zoom));
			
			
			m_pHeightMap[bottom] = (short)((m_pHeightMap[leftbottom] + m_pHeightMap[curmid] + m_pHeightMap[rightbottom] + GetBottomHeight(bottom, curmid)) / 4 + GetRandomHeight(zoom));

			RandHeightMapSD(lefttop, top, curmid, left, zoom * 0.5f);
			RandHeightMapSD(top, righttop, right, curmid, zoom * 0.5f);
			RandHeightMapSD(curmid, right, rightbottom, bottom, zoom * 0.5f);
			RandHeightMapSD(left, curmid, bottom, leftbottom, zoom * 0.5f);
		}

		short CRandomTerrain::GetHeight(uint x, uint y)
		{
			return m_pHeightMap[y * (m_uWidth + 1) + x];
		}

		void CRandomTerrain::GenerateMesh()
		{
			//生成顶点
			SVertex *pVertices = m_pMeshData->pVertices;			
			int k = 0;
			for (uint i = 0; i < m_uWidth; ++i)
			{
				for (uint j = 0; j < m_uWidth; ++j)
				{
					pVertices[k].vPosition = core::CVector3((float)j - m_uWidth / 2, (float)GetHeight(j, i), (float)i - m_uWidth / 2);
					pVertices[k].u = 1.0f * j / (m_uWidth + 1);
					pVertices[k].v = 1.0f * i / (m_uWidth + 1);
					++k;
				}
			}

			//生成索引
			uint j = 0;
			uint z = 0;
			uint *pIndices = m_pMeshData->pIndices;
			while (z < m_uWidth - 1)
			{
				for (uint x = 0; x < m_uWidth; x++)
				{
					pIndices[j++] = x + z * m_uWidth;
					pIndices[j++] = x + (z + 1) * m_uWidth;
				}
				z++;

				if (z < m_uWidth - 1)
				{
					for (int x = int(m_uWidth) - 1; x >= 0; x--)
					{
						pIndices[j++] = x + (z + 1) * m_uWidth;
						pIndices[j++] = x + z * m_uWidth;
					}
				}
				z++;
			}


			//生成法线
			for (uint i = 0; i < m_pMeshData->uIdsNum - 3; i += 3) 
			{
				unsigned int Index0 = pIndices[i];
				unsigned int Index1 = pIndices[i + 1];
				unsigned int Index2 = pIndices[i + 2];
				core::CVector3 v1 = pVertices[Index1].vPosition - pVertices[Index0].vPosition;
				core::CVector3 v2 = pVertices[Index2].vPosition - pVertices[Index0].vPosition;
				core::CVector3 vNormal = v1.crossProduct(v2);
				vNormal.normalize();
				pVertices[Index0].vNormal += vNormal;
				pVertices[Index1].vNormal += vNormal;
				pVertices[Index2].vNormal += vNormal;
			}
			for (unsigned int i = 0; i < m_pMeshData->uVertNum; ++i) {
				pVertices[i].vNormal.normalize();
			}

			m_pGPUBuffer = m_pRenderer->CreateGPUBuffer();
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
						shaderProgram->BindAttributeLocation(3, render::VAL_POSITION, render::VAL_TEXTURE0, render::VAL_NORMAL);
						shaderProgram->Link();
						int iTextureUnit = 0;
						shaderProgram->SetUniform("textureUnit0", &iTextureUnit);
						shaderProgram->SetUniform("ambientColor", core::CVector3(.8f, .8f, .8f).v);
						shaderProgram->SetUniform("diffuseColor", core::CVector3(0.8f, 0.8f, 0.8f).v);
						shaderProgram->SetUniform("specularColor", core::CVector3(1.0f, 1.0f, 1.0f).v);
					}
				}
				m_pGPUBuffer->Begin();
				m_pRenderableObject->CreateVertexBufferObject(m_pMeshData->pVertices, m_pMeshData->uVertNum * sizeof(SVertex), 0, m_pMeshData->uVertNum, render::GBM_TRIANGLE_STKIP, render::GBU_DYNAMIC_DRAW);
				m_pRenderableObject->CreateIndexBufferObject(m_pMeshData->pIndices, m_pMeshData->uIdsNum, render::RVT_UINT, m_pMeshData->uVertNum, render::GBM_TRIANGLE_STKIP, render::GBU_DYNAMIC_DRAW);
				m_pGPUBuffer->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, sizeof(SVertex), 0);
				m_pGPUBuffer->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, sizeof(SVertex), sizeof(float)* 6);
				m_pGPUBuffer->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, sizeof(SVertex), sizeof(float)* 3);

				m_pGPUBuffer->End();

				
				m_pTextureGenerator = m_pRenderer->GetTextureGenerator();
				if (m_pTextureGenerator)
				{
					char *filename[] = {"texture/land.tga", "texture/land.tga", "texture/land.tga"};					
					m_pTexture = m_pTextureGenerator->GenerateTextureBit24(m_pHeightMap, m_uWidth + 1, MAX_HEIGHT, filename, 3);
					m_pRenderableObject->SetTexture(m_pTexture);
				}
			}
		}

		void CRandomTerrain::Update(int elapsedTime, const core::CMatrix4 &mat4MVP, const core::CMatrix4 &mat4MV)
		{
			if (m_pRenderableObject)
			{
				render::IShaderProgram *shaderProgram = m_pRenderableObject->GetShaderProgram();
				if (shaderProgram)
				{
					shaderProgram->SetUniform("mvpMatrix", (void *)mat4MVP.m);
					shaderProgram->SetUniform("mvMatrix", (void *)mat4MV.m);
					shaderProgram->SetUniform("normalMatrix", (void *)mat4MV.m);
					static float rot = 0.1f;
					if (rot > 3.14159)
						rot = .0;
					rot += 0.01f;
					core::CVector3 vLight(0, 500, 0);
					vLight.rotateXZBy(rot);
					shaderProgram->SetUniform("vLightPosition", (void *)vLight.v);
				}
			}
		}

		short CRandomTerrain::GetLeftHeight(uint high, uint low)
		{
			uint pos = 2 * low - high;
			if (pos / (m_uWidth + 1) == low / (m_uWidth + 1))
				return m_pHeightMap[pos];
			return m_pHeightMap[high];
		}

		short CRandomTerrain::GetTopHeight(uint high, uint low)
		{
			uint pos = 2 * low - high;
			if (pos % (m_uWidth + 1) == low % (m_uWidth + 1) && pos > 0)
				return m_pHeightMap[pos];
			return m_pHeightMap[high];
		}

		short CRandomTerrain::GetRightHeight(uint high, uint low)
		{
			uint pos = 2 * (high - low) + low;
			if (pos / (m_uWidth + 1) == low / (m_uWidth + 1))
				return m_pHeightMap[pos];
			return m_pHeightMap[low];
		}

		short CRandomTerrain::GetBottomHeight(uint high, uint low)
		{
			uint pos = 2 * (high - low) + low;
			if (pos % (m_uWidth + 1) == low % (m_uWidth + 1) && pos < (m_uWidth + 1) * (m_uWidth + 1))
				return m_pHeightMap[pos];
			return m_pHeightMap[low];
		}

		float CRandomTerrain::GetRandomHeight(float zoom)
		{
			int scale = (int)(zoom * (MAX_HEIGHT + 1));
			if (scale == 0)
				return 0;
			return  (rand() % scale - scale * 0.5f);
		}

		short CRandomTerrain::GetMaxAndmin(short &maxValue, short &minValue, short value1, short value2, short value3, short value4)
		{
			maxValue = minValue = value1;
			maxValue = MAX(maxValue, value2);
			maxValue = MAX(maxValue, value3);
			maxValue = MAX(maxValue, value4);

			minValue = MIN(minValue, value2);
			minValue = MIN(minValue, value3);
			minValue = MIN(minValue, value4);

			return maxValue - minValue;
		}

		float CRandomTerrain::GetRandomHeight(short base, short range)
		{
			return float (rand() % range + base);
		}


	}
		
}