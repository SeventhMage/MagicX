#include "CTerrainEntity.h"
#include "IGPUBuffer.h"
#include "IRenderableObject.h"
#include "IShaderProgram.h"


#include <time.h>


namespace mx
{
	namespace scene
	{
		CTerrainEntity::CTerrainEntity(render::IRenderer *renderer, uint width)
			:m_uWidth(width)
			,m_pRenderer(renderer)
			, m_pGPUBuffer(NULL)
			, m_pRenderableObject(NULL)
		{
			m_pHeightMap = new short[(width + 1) * (width + 1)];
			memset(m_pHeightMap, 0, sizeof(short) * ((width + 1) * (width + 1)));

			m_pMeshData = new float[6 * 3 * width * width];

		}
		CTerrainEntity::~CTerrainEntity()
		{
			SAFE_DEL(m_pHeightMap);
			if (m_pRenderer)
				m_pRenderer->DestroyGPUBuffer(m_pGPUBuffer);
		}

		void CTerrainEntity::RandGenerateMesh()
		{
			RandHeightMap();
			GenerateMesh();
		}

		void CTerrainEntity::RandHeightMap()
		{
			srand(time(0));
			uint size = (m_uWidth + 1) * (m_uWidth + 1);
			for (uint i = 0; i < size; ++i)
			{
				short height = rand() % 4 - 2;
				m_pHeightMap[i] = height;
			}
			
			int var = m_uWidth;
			float zoom = 1.0f;
			int lefttop = 0;
			int righttop = m_uWidth;
			int leftbottom = (m_uWidth + 1) * (m_uWidth + 1);
			int rightbottom = leftbottom + m_uWidth;
			while (var > 1)
			{
				m_pHeightMap[lefttop] = (rand() % 256 - 128) * zoom;
				m_pHeightMap[righttop] = (rand() % 256 - 128) * zoom;
				m_pHeightMap[leftbottom] = (rand() % 256 - 128) * zoom;
				m_pHeightMap[rightbottom] = (rand() % 256 - 128) * zoom;

				zoom *= 0.5f;
				m_pHeightMap[(var / 2) * var + var] = (m_pHeightMap[0] + m_pHeightMap[var] + m_pHeightMap[(var + 1) * (var + 1)] + m_pHeightMap[(var + 1) * (var + 1) + var]) / 4 
					+ (rand() % 256 - 128) * zoom;

				var /= 2;
			}
			
		}

		float CTerrainEntity::RandHeightMap(int left, int top, int right, int bottom, float zoom)
		{
			m_pHeightMap[left] = (rand() % 256 - 128) * zoom;
			m_pHeightMap[top] = (rand() % 256 - 128) * zoom;
			m_pHeightMap[right] = (rand() % 256 - 128) * zoom;
			m_pHeightMap[bottom] = (rand() % 256 - 128) * zoom;

			zoom *= 0.5f;

			m_pHeightMap[(left - top) / 2 + top] = (m_pHeightMap[top] + m_pHeightMap[left] + m_pHeightMap[top / (m_uWidth + 1) * (m_uWidth + 1) + left % (m_uWidth + 1)]
				+ m_pHeightMap[left / (m_uWidth + 1) * (m_uWidth + 1) + (top % (m_uWidth + 1))]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(right - top) / 2 + top] = (m_pHeightMap[top] + m_pHeightMap[right] + m_pHeightMap[top / (m_uWidth + 1) * (m_uWidth + 1) + right % (m_uWidth + 1)]
				+ m_pHeightMap[right / (m_uWidth + 1) * (m_uWidth + 1) + top % (m_uWidth + 1)]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(bottom - left) / 2 + left] = (m_pHeightMap[left] + m_pHeightMap[bottom] + m_pHeightMap[left / (m_uWidth + 1) * (m_uWidth + 1) + bottom % (m_uWidth + 1)]
				+ m_pHeightMap[(bottom / (m_uWidth + 1) * (m_uWidth + 1) + left % (m_uWidth + 1))]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(bottom - right) / 2 + right] = (m_pHeightMap[right] + m_pHeightMap[top] + m_pHeightMap[right % (m_uWidth + 1) * (m_uWidth + 1) + bottom % (m_uWidth + 1)]
				+ m_pHeightMap[bottom / (m_uWidth + 1) * (m_uWidth + 1) + right % (m_uWidth + 1)]) / 4 + (rand() % 256 - 128) * zoom;

			RandHeightMap((((left - top) / 2 + top) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((left - top) / 2 + top) % (m_uWidth + 1)
				, 
				, (((bottom - left) / 2 + left) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((bottom - left) / 2 + left) % (m_uWidth + 1)
				, (((bottom - right) / 2 + right) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((bottom - right) / 2 + right) % (m_uWidth + 1)
				,zoom
				);
			RandHeightMap((((left - top) / 2 + top) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((left - top) / 2 + top) % (m_uWidth + 1)
				, (((right - top) / 2 + top) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((right - top) / 2 + top) % (m_uWidth + 1)
				, (((bottom - left) / 2 + left) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((bottom - left) / 2 + left) % (m_uWidth + 1)
				, (((bottom - right) / 2 + right) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((bottom - right) / 2 + right) % (m_uWidth + 1)
				, zoom
				);
			RandHeightMap((((left - top) / 2 + top) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((left - top) / 2 + top) % (m_uWidth + 1)
				, (((right - top) / 2 + top) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((right - top) / 2 + top) % (m_uWidth + 1)
				, (((bottom - left) / 2 + left) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((bottom - left) / 2 + left) % (m_uWidth + 1)
				, (((bottom - right) / 2 + right) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((bottom - right) / 2 + right) % (m_uWidth + 1)
				, zoom
				);
			RandHeightMap((((left - top) / 2 + top) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((left - top) / 2 + top) % (m_uWidth + 1)
				, (((right - top) / 2 + top) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((right - top) / 2 + top) % (m_uWidth + 1)
				, (((bottom - left) / 2 + left) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((bottom - left) / 2 + left) % (m_uWidth + 1)
				, (((bottom - right) / 2 + right) / (m_uWidth + 1) - 1) * (m_uWidth + 1) + ((bottom - right) / 2 + right) % (m_uWidth + 1)
				, zoom
				);
			return zoom;

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
					m_pMeshData[k++] = (float)i - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j, i);
					m_pMeshData[k++] = (float)j - m_uWidth / 2;

					m_pMeshData[k++] = (float)i + 1 - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j, i + 1);
					m_pMeshData[k++] = (float)j - m_uWidth / 2;

					m_pMeshData[k++] = (float)i - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j + 1, i);
					m_pMeshData[k++] = (float)j + 1 - m_uWidth / 2;

					m_pMeshData[k++] = (float)i - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j + 1, i);
					m_pMeshData[k++] = (float)j + 1 - m_uWidth / 2;

					m_pMeshData[k++] = (float)i + 1 - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j, i + 1);
					m_pMeshData[k++] = (float)j - m_uWidth / 2;

					m_pMeshData[k++] = (float)i + 1 - m_uWidth / 2;
					m_pMeshData[k++] = (float)GetHeight(j + 1, i + 1);
					m_pMeshData[k++] = (float)j + 1 - m_uWidth / 2;
				}
			}

			m_pGPUBuffer = m_pRenderer->CreateGPUBuffer(0);
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
						shaderProgram->BindAttributeLocation(1, render::VAL_POSITION);
						shaderProgram->Link();
					}
				}
				m_pGPUBuffer->Begin();
				m_pGPUBuffer->CreateVertexBuffer(m_pRenderableObject, m_pMeshData, sizeof(float) * (6 * 3 * m_uWidth * m_uWidth), 0, 6 * 3 * m_uWidth * m_uWidth, render::GBM_TRIANGLES, render::GBU_DYNAMIC_DRAW);
				m_pGPUBuffer->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0);

				m_pGPUBuffer->End();
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


	}
		
}