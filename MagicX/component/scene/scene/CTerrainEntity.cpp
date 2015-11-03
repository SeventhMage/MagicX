#include <time.h>

#include "CTerrainEntity.h"
#include "IGPUBuffer.h"
#include "IRenderableObject.h"
#include "IShaderProgram.h"



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
		
			int var = m_uWidth;
			float zoom = 1.0f;
			int lefttop = 0;
			int righttop = m_uWidth;
			int leftbottom = (m_uWidth + 1) * m_uWidth;
			int rightbottom = leftbottom + m_uWidth;
		
			m_pHeightMap[lefttop] = (short)GetRandomHeight(zoom);
			m_pHeightMap[righttop] = (short)GetRandomHeight(zoom);
			m_pHeightMap[leftbottom] = (short)GetRandomHeight(zoom);
			m_pHeightMap[rightbottom] = (short)GetRandomHeight(zoom);

			//zoom *= 0.5f;

			//int left = (m_uWidth / 2) * (m_uWidth + 1);
			//int top = m_uWidth / 2;
			//int right = left + m_uWidth;
			//int bottom = m_uWidth * (m_uWidth + 1) + (m_uWidth / 2);

			//m_pHeightMap[(leftbottom - righttop) / 2 + rightbottom] = zoom * ((m_pHeightMap[lefttop] + m_pHeightMap[righttop] + m_pHeightMap[leftbottom] + m_pHeightMap[rightbottom]) / 4.0f) * (rand() % 256);

			RandHeightMapSD(lefttop, righttop, rightbottom, leftbottom, 0.5f);
			
		}


		void CTerrainEntity::RandHeightMapSD(int lefttop, int righttop, int rightbottom, int leftbottom, float zoom)
		{
			if (righttop - lefttop <= 1)
				return;
			int curmid = (leftbottom - righttop) / 2 + righttop;
			m_pHeightMap[curmid] = (short)(((m_pHeightMap[lefttop] + m_pHeightMap[righttop] + m_pHeightMap[leftbottom] + m_pHeightMap[rightbottom]) / 4.0f) + GetRandomHeight(zoom));
			
			int left = lefttop + (leftbottom - lefttop) / 2;
			int top = lefttop + (righttop - lefttop) / 2;
			int right = righttop + (rightbottom - righttop) / 2;
			int bottom = leftbottom + (rightbottom - leftbottom) / 2;
			
			m_pHeightMap[left] = (short)((m_pHeightMap[lefttop] + m_pHeightMap[curmid] + m_pHeightMap[leftbottom] + GetLeftHeight(curmid, left)) / 4 +  GetRandomHeight(zoom));
			m_pHeightMap[top] = (short)((m_pHeightMap[lefttop] + m_pHeightMap[curmid] + m_pHeightMap[righttop] + GetTopHeight(curmid, top)) / 4 + GetRandomHeight(zoom));
			m_pHeightMap[right] = (short)((m_pHeightMap[curmid], m_pHeightMap[righttop] + m_pHeightMap[rightbottom] + GetRightHeight(right, curmid)) / 4 + GetRandomHeight(zoom));
			m_pHeightMap[bottom] = (short)((m_pHeightMap[leftbottom] + m_pHeightMap[curmid] + m_pHeightMap[rightbottom] + GetBottomHeight(bottom, curmid)) / 4 + GetRandomHeight(zoom));

			/*
			m_pHeightMap[(left - top) / 2 + top] = (m_pHeightMap[top] + m_pHeightMap[left] + m_pHeightMap[top / (m_uWidth + 1) * (m_uWidth + 1) + left % (m_uWidth + 1)]
				+ m_pHeightMap[left / (m_uWidth + 1) * (m_uWidth + 1) + (top % (m_uWidth + 1))]) / 4 + (rand() % MAX_HEIGHT) * zoom;

			m_pHeightMap[(right - top) / 2 + top] = (m_pHeightMap[top] + m_pHeightMap[right] + m_pHeightMap[top / (m_uWidth + 1) * (m_uWidth + 1) + right % (m_uWidth + 1)]
				+ m_pHeightMap[right / (m_uWidth + 1) * (m_uWidth + 1) + top % (m_uWidth + 1)]) / 4 + (rand() % MAX_HEIGHT) * zoom;

			m_pHeightMap[(bottom - left) / 2 + left] = (m_pHeightMap[left] + m_pHeightMap[bottom] + m_pHeightMap[left / (m_uWidth + 1) * (m_uWidth + 1) + bottom % (m_uWidth + 1)]
				+ m_pHeightMap[(bottom / (m_uWidth + 1) * (m_uWidth + 1) + left % (m_uWidth + 1))]) / 4 + (rand() % MAX_HEIGHT) * zoom;

			m_pHeightMap[(bottom - right) / 2 + right] = (m_pHeightMap[right] + m_pHeightMap[top] + m_pHeightMap[right % (m_uWidth + 1) * (m_uWidth + 1) + bottom % (m_uWidth + 1)]
				+ m_pHeightMap[bottom / (m_uWidth + 1) * (m_uWidth + 1) + right % (m_uWidth + 1)]) / 4 + (rand() % MAX_HEIGHT) * zoom;
				

			RandHeightMapSD((left - top) / 2 + top, (right - top) / 2 + top, (bottom - right) / 2 + right, (bottom - left) / 2 + left, zoom * 0.5f);
			*/

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
			return m_pHeightMap[high];
		}

		short CTerrainEntity::GetBottomHeight(uint high, uint low)
		{
			uint pos = 2 * (high - low) + low;
			if (pos % (m_uWidth + 1) == low % (m_uWidth + 1) && pos < (m_uWidth + 1) * (m_uWidth + 1))
				return m_pHeightMap[pos];
			return m_pHeightMap[high];
		}

		float CTerrainEntity::GetRandomHeight(float zoom)
		{
			return zoom * (rand() % MAX_HEIGHT - MAX_HEIGHT * 0.5f);
		}


	}
		
}