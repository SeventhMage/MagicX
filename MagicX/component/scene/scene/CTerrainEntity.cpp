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