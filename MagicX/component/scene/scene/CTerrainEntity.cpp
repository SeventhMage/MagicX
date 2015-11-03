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
		
			int var = m_uWidth;
			float zoom = 1.0f;
			int lefttop = 0;
			int righttop = m_uWidth;
			int leftbottom = (m_uWidth + 1) * (m_uWidth + 1);
			int rightbottom = leftbottom + m_uWidth;
		
			m_pHeightMap[lefttop] = (rand() % MAX_HEIGHT - 0) * zoom;
			m_pHeightMap[righttop] = (rand() % MAX_HEIGHT - 0) * zoom;
			m_pHeightMap[leftbottom] = (rand() % MAX_HEIGHT - 0) * zoom;
			m_pHeightMap[rightbottom] = (rand() % MAX_HEIGHT - 0) * zoom;

			//zoom *= 0.5f;

			//int left = (m_uWidth / 2) * (m_uWidth + 1);
			//int top = m_uWidth / 2;
			//int right = left + m_uWidth;
			//int bottom = m_uWidth * (m_uWidth + 1) + (m_uWidth / 2);

			//m_pHeightMap[(leftbottom - righttop) / 2 + rightbottom] = zoom * ((m_pHeightMap[lefttop] + m_pHeightMap[righttop] + m_pHeightMap[leftbottom] + m_pHeightMap[rightbottom]) / 4.0f) * (rand() % 256);

			RandHeightMapSD(lefttop, righttop, rightbottom, leftbottom, 1.0f);
			
		}

		float CTerrainEntity::RandHeightMap(int left, int top, int right, int bottom, float zoom)
		{
			m_pHeightMap[left] = (rand() % 256 - 0) * zoom;
			m_pHeightMap[top] = (rand() % 256 - 0) * zoom;
			m_pHeightMap[right] = (rand() % 256 - 0) * zoom;
			m_pHeightMap[bottom] = (rand() % 256 - 0) * zoom;

			CVector3 vec3Left(left % (m_uWidth + 1), left / (m_uWidth + 1), 0);
			CVector3 vec3Top(top % (m_uWidth + 1), top / (m_uWidth + 1), 0);
			CVector3 vec3Right(right % (m_uWidth + 1), right / (m_uWidth + 1), 0);
			CVector3 vec3Bottom(bottom % (m_uWidth + 1), bottom / (m_uWidth + 1), 0);

		
			zoom *= 0.5f;

			m_pHeightMap[(left - top) / 2 + top] = (m_pHeightMap[top] + m_pHeightMap[left] + m_pHeightMap[top / (m_uWidth + 1) * (m_uWidth + 1) + left % (m_uWidth + 1)]
				+ m_pHeightMap[left / (m_uWidth + 1) * (m_uWidth + 1) + (top % (m_uWidth + 1))]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(right - top) / 2 + top] = (m_pHeightMap[top] + m_pHeightMap[right] + m_pHeightMap[top / (m_uWidth + 1) * (m_uWidth + 1) + right % (m_uWidth + 1)]
				+ m_pHeightMap[right / (m_uWidth + 1) * (m_uWidth + 1) + top % (m_uWidth + 1)]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(bottom - left) / 2 + left] = (m_pHeightMap[left] + m_pHeightMap[bottom] + m_pHeightMap[left / (m_uWidth + 1) * (m_uWidth + 1) + bottom % (m_uWidth + 1)]
				+ m_pHeightMap[(bottom / (m_uWidth + 1) * (m_uWidth + 1) + left % (m_uWidth + 1))]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(bottom - right) / 2 + right] = (m_pHeightMap[right] + m_pHeightMap[top] + m_pHeightMap[right % (m_uWidth + 1) * (m_uWidth + 1) + bottom % (m_uWidth + 1)]
				+ m_pHeightMap[bottom / (m_uWidth + 1) * (m_uWidth + 1) + right % (m_uWidth + 1)]) / 4 + (rand() % 256 - 128) * zoom;

			if (vec3Left.x + 1 == vec3Top.x || vec3Top.y + 1 == vec3Left.y)
				return zoom;

			CVector3 lefttopMid(((left - top) / 2 + top) % (m_uWidth + 1), ((left - top) / 2 + top) / (m_uWidth + 1), 0);
			CVector3 righttopMid(((right - top) / 2 + top) % (m_uWidth + 1), ((right - top) / 2 + top) / (m_uWidth + 1), 0);
			CVector3 leftbottomMid(((bottom - left) / 2 + left) % (m_uWidth + 1), ((bottom - left) / 2 + left) / (m_uWidth + 1), 0);
			CVector3 rightbottomMid(((bottom - right) / 2 + right) % (m_uWidth + 1), ((bottom - right) / 2 + right) / (m_uWidth + 1), 0);

		

			RandHeightMap(
				lefttopMid.y * (m_uWidth + 1) + vec3Left.x
				,vec3Top.y * (m_uWidth + 1) + lefttopMid.x
				,lefttopMid.y * (m_uWidth + 1) + vec3Top.x
				,vec3Left.y * (m_uWidth + 1) + lefttopMid.x
				,zoom
				);
			RandHeightMap(
				righttopMid.y * (m_uWidth + 1) + vec3Top.x
				,vec3Top.y * (m_uWidth + 1) + righttopMid.x
				,righttopMid.y * (m_uWidth + 1) + vec3Right.x
				,vec3Right.y * (m_uWidth + 1) + righttopMid.x
				,zoom
				);

			RandHeightMap(
				leftbottomMid.y * (m_uWidth + 1) + vec3Left.x
				,vec3Left.y * (m_uWidth + 1) + leftbottomMid.x
				,leftbottomMid.y * (m_uWidth + 1) + vec3Bottom.x
				,vec3Bottom.y * (m_uWidth + 1) + leftbottomMid.x
				,zoom
				);

			RandHeightMap(
				rightbottomMid.y * (m_uWidth + 1) + vec3Bottom.x
				,vec3Right.y * (m_uWidth + 1) + rightbottomMid.x
				,rightbottomMid.y * (m_uWidth + 1) + vec3Right.x
				,vec3Bottom.y * (m_uWidth + 1) + rightbottomMid.x
				,zoom
				);

			return zoom;

		}

		void CTerrainEntity::RandHeightMapSD(int lefttop, int righttop, int rightbottom, int leftbottom, float zoom)
		{
			if (righttop - lefttop <= 1)
				return;
			int curmid = (leftbottom - righttop) / 2 + rightbottom;
			m_pHeightMap[curmid] = (((m_pHeightMap[lefttop] + m_pHeightMap[righttop] + m_pHeightMap[leftbottom] + m_pHeightMap[rightbottom]) / 4.0f) + zoom * (rand() % MAX_HEIGHT));
			
			int left = lefttop + (leftbottom - lefttop) / 2;
			int top = lefttop + (righttop - lefttop) / 2;
			int right = righttop + (rightbottom - righttop) / 2;
			int bottom = leftbottom + (rightbottom - leftbottom) / 2;
			
			m_pHeightMap[left] =  ((m_pHeightMap[lefttop] + m_pHeightMap[curmid] + m_pHeightMap[leftbottom] + GetLeftHeight(curmid, left)) / 4 + zoom * (rand() % MAX_HEIGHT));
			m_pHeightMap[top] =  ((m_pHeightMap[lefttop] + m_pHeightMap[curmid] + m_pHeightMap[righttop] + GetTopHeight(curmid, top)) / 4 + zoom * (rand() % MAX_HEIGHT));
			m_pHeightMap[right] = (m_pHeightMap[curmid], m_pHeightMap[righttop] + m_pHeightMap[rightbottom] + GetRightHeight(right, curmid)) / 4 + zoom * (rand() % MAX_HEIGHT);
			m_pHeightMap[bottom] = (m_pHeightMap[leftbottom] + m_pHeightMap[curmid] + m_pHeightMap[rightbottom] + GetBottomHeight(bottom, curmid)) / 4 + zoom * (rand() % MAX_HEIGHT);

			m_pHeightMap[(left - top) / 2 + top] = (m_pHeightMap[top] + m_pHeightMap[left] + m_pHeightMap[top / (m_uWidth + 1) * (m_uWidth + 1) + left % (m_uWidth + 1)]
				+ m_pHeightMap[left / (m_uWidth + 1) * (m_uWidth + 1) + (top % (m_uWidth + 1))]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(right - top) / 2 + top] = (m_pHeightMap[top] + m_pHeightMap[right] + m_pHeightMap[top / (m_uWidth + 1) * (m_uWidth + 1) + right % (m_uWidth + 1)]
				+ m_pHeightMap[right / (m_uWidth + 1) * (m_uWidth + 1) + top % (m_uWidth + 1)]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(bottom - left) / 2 + left] = (m_pHeightMap[left] + m_pHeightMap[bottom] + m_pHeightMap[left / (m_uWidth + 1) * (m_uWidth + 1) + bottom % (m_uWidth + 1)]
				+ m_pHeightMap[(bottom / (m_uWidth + 1) * (m_uWidth + 1) + left % (m_uWidth + 1))]) / 4 + (rand() % 256 - 128) * zoom;

			m_pHeightMap[(bottom - right) / 2 + right] = (m_pHeightMap[right] + m_pHeightMap[top] + m_pHeightMap[right % (m_uWidth + 1) * (m_uWidth + 1) + bottom % (m_uWidth + 1)]
				+ m_pHeightMap[bottom / (m_uWidth + 1) * (m_uWidth + 1) + right % (m_uWidth + 1)]) / 4 + (rand() % 256 - 128) * zoom;

			RandHeightMapSD((left - top) / 2 + top, (right - top) / 2 + top, (bottom - right) / 2 + right, (bottom - left) / 2 + left, zoom * 0.5f);
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

		int CTerrainEntity::GetLeftHeight(int high, int low)
		{
			int pos = 2 * low - high;
			if (pos / (m_uWidth + 1) == low / (m_uWidth + 1))
				return m_pHeightMap[pos];
			return 0;
		}

		int CTerrainEntity::GetTopHeight(int high, int low)
		{
			int pos = 2 * low - high;
			if (pos % (m_uWidth + 1) == low % (m_uWidth + 1))
				return m_pHeightMap[pos];
			return 0;
		}

		int CTerrainEntity::GetRightHeight(int high, int low)
		{
			int pos = 2 * (high - low) + low;
			if (pos / (m_uWidth + 1) == low / (m_uWidth + 1))
				return m_pHeightMap[pos];
			return 0;
		}

		int CTerrainEntity::GetBottomHeight(int high, int low)
		{
			int pos = 2 * (high - low) + low;
			if (pos % (m_uWidth + 1) == low % (m_uWidth + 1))
				return m_pHeightMap[pos];
			return 0;
		}


	}
		
}