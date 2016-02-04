#include <string.h>

#include "CMesh.h"
#include "CPLXLoader.h"
#include "core/CMatrix4.h"
#include "render/SVertexAttribute.h"
#include "render/SColor.h"

namespace mx
{
	namespace resource
	{
		using namespace render;

		CMesh::CMesh(render::IGPUBuffer *pGPUBuffer)
			:m_uId(0), m_uState(0), m_uAttr(0), m_fAvgRadius(0), m_fMaxRadius(0), m_uVerticesNum(0), m_pvLocalList(0)
			, m_pvTransList(0), m_uTriangleNum(0), m_pTriangleList(0), m_pGPUBuffer(pGPUBuffer), m_pRenderableObject(NULL)
		{
			memset(m_szName, 0, sizeof(m_szName));
		}

		CMesh::~CMesh()
		{
			SAFE_DEL_ARRAY(m_pvLocalList);
			SAFE_DEL_ARRAY(m_pvTransList);
			SAFE_DEL_ARRAY(m_pTriangleList);
		}

		void CMesh::CalculateBoundingBox()
		{

		}

		void CMesh::CalculateRadius()
		{

		}

		bool CMesh::Load(const char *filename)
		{
			bool bRet = false;
			const char *extPos = strrchr(filename, '.');
			if (extPos)
			{
				if (0 == strcmp(extPos, ".plg") || 0 == strcmp(extPos, ".plx"))
				{
					CPLXLoader loader;
					loader.LoadResource(filename, this);
					for (uint i = 0; i < m_uTriangleNum; ++i)
					{
						CreatePLXRenderable(i);
					}
					bRet = true;
				}
			}

			return bRet;
		}

		void CMesh::rotateXZBy(double radians, const CVector3 &center /*= CVector3(0, 1.0f, 0)*/)
		{
			for (uint i = 0; i < m_uVerticesNum; ++i)
			{
				m_pvLocalList[i].rotateXZBy(radians, center);
			}
		}

		void CMesh::rotateXYBy(double radians, const CVector3 &center /*= CVector3(0, 0, 1.0f)*/)
		{
			for (uint i = 0; i < m_uVerticesNum; ++i)
			{
				m_pvLocalList[i].rotateXYBy(radians, center);
			}
		}

		void CMesh::rotateYZBy(double radians, const CVector3 &center /*= CVector3(1.0f, 0, 0)*/)
		{
			for (uint i = 0; i < m_uVerticesNum; ++i)
			{
				m_pvLocalList[i].rotateYZBy(radians, center);
			}
		}

		void CMesh::Update(uint deltaTime)
		{
			if (m_pRenderableObject)
			{
				IBufferObject *bufferObject = m_pRenderableObject->GetVertexBufferObject();
				if (bufferObject)
				{
					bufferObject->BufferData(m_pvLocalList, sizeof(CVector3) * m_uVerticesNum);
				}
			}
		}

		void CMesh::CreatePLXRenderable(uint idx)
		{
			m_pRenderableObject = m_pGPUBuffer->CreateRenderableObject();
			if (m_pRenderableObject)
			{
				m_pRenderableObject->SetPolygonMode(PM_LINE);
				m_pRenderableObject->Disable(RA_CULL_FACE);
				render::IShaderProgram *shaderProgram = m_pRenderableObject->GetShaderProgram();
				if (shaderProgram)
				{
					shaderProgram->CreateStandShader(ESS_SHADER_FLAT);
					CMatrix4 projectMat4;
					projectMat4.buildProjectionMatrixPerspectiveFovRH(PI / 2.0f, 3.0f / 4.0f, 1, 1000.0f);
					CMatrix4 viewMat4;
					viewMat4.buildCameraLookAtMatrix(CVector3(0, 0, 0), CVector3(0, 0, -1), CVector3(0, 1, 0));
					CMatrix4 modelMat4;
					modelMat4.setTranslation(CVector3(0, 0, -50.0f));

					CMatrix4 mvpMat4 = projectMat4 * viewMat4 * modelMat4;

					shaderProgram->SetUniform("mvpMatrix", &mvpMat4.m);
					
					SColor color(m_pTriangleList[idx].color);
					float fColor[] = { color.GetRed() / 255.0f, color.GetGreen() / 255.0f, color.GetBlue() / 255.0f, color.GetAlpha() / 255.0f};
					shaderProgram->SetUniform("vColor", fColor);
				}
				
				m_pGPUBuffer->Begin();
				m_pRenderableObject->CreateVertexBufferObject(m_pvLocalList, sizeof(CVector3)* m_uVerticesNum, 0, m_uVerticesNum, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pRenderableObject->CreateIndexBufferObject(m_pTriangleList[idx].indices, 3, RVT_UINT, m_uVerticesNum, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pGPUBuffer->EnableVertexAttrib(VAL_POSITION, 3, RVT_FLOAT, sizeof(CVector3), 0);
				m_pGPUBuffer->End();
			}
		}

	}
}