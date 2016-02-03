#include <string.h>

#include "CMesh.h"
#include "CPLXLoader.h"
#include "core/CMatrix4.h"
#include "render/SVertexAttribute.h"

namespace mx
{
	namespace resource
	{
		using namespace render;

		CMesh::CMesh(render::IGPUBuffer *pGPUBuffer)
			:m_uId(0), m_uState(0), m_uAttr(0), m_fAvgRadius(0), m_fMaxRadius(0), m_uVerticesNum(0), m_pvLocalList(0)
			, m_pvTransList(0), m_uTriangleNum(0), m_pTriangleList(0), m_pGPUBuffer(pGPUBuffer)
		{
			memset(m_szName, 0, sizeof(m_szName));
		}

		CMesh::~CMesh()
		{
			SAFE_DEL_ARRAY(m_pIndecisData);
			SAFE_DEL_ARRAY(m_pVerticesData);
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

					bRet = true;
				}
			}

			if (bRet)
			{
				render::IRenderableObject *renderableObject = m_pGPUBuffer->CreateRenderableObject();
				if (renderableObject)
				{
					render::IShaderProgram *shaderProgram = renderableObject->GetShaderProgram();
					if (shaderProgram)
					{
						shaderProgram->CreateStandShader(ESS_SHADER_FLAT);
						CMatrix4 projectMat4;
						projectMat4.buildProjectionMatrixPerspectiveFovRH(PI / 2.0f, 1.0f * 3.0f / 4.0f, 1, 100.0f);
						CMatrix4 viewMat4;
						viewMat4.buildCameraLookAtMatrix(CVector3(8, 0, 4), CVector3(0, 0, -1), CVector3(0, 1, 0));
						CMatrix4 modelMat4;
						modelMat4.setTranslation(CVector3(0, 0, -20.0f));

						CMatrix4 mvpMat4 = projectMat4 * viewMat4 * modelMat4;

						shaderProgram->SetUniform("mvpMatrix", &mvpMat4.m);

						float color[] = { .5f, 1.0f, 0.5f, 0.5f };
						shaderProgram->SetUniform("vColor", color);
					}

					m_pGPUBuffer->Begin();
					renderableObject->CreateVertexBufferObject(GetVerticesData(), GetVerticesSize(), 0, GetVerticesCount(), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
					renderableObject->CreateIndexBufferObject(GetIndicesData(), GetIndicesCount(), RVT_UINT, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
					m_pGPUBuffer->EnableVertexAttrib(VAL_POSITION, 4, RVT_FLOAT, GetVertexStride(), 0);					
					m_pGPUBuffer->End();
				}
			}

			return bRet;
		}

		byte * CMesh::GetVerticesData() const
		{
			return (byte *)m_pVerticesData;
		}

		mx::uint CMesh::GetVerticesSize() const
		{
			return sizeof(float) * 4 * m_uVerticesNum;
		}

		mx::uint CMesh::GetVerticesCount() const
		{
			return m_uVerticesNum;
		}

		mx::uint CMesh::GetVertexStride() const
		{
			return sizeof(float) * 4;
		}

		byte * CMesh::GetIndicesData() const
		{
			return (byte *)m_pIndecisData;
		}

		mx::uint CMesh::GetIndicesSize() const
		{
			return m_uTriangleNum * sizeof(int) * 3;
		}

		mx::uint CMesh::GetIndicesCount() const
		{
			return m_uTriangleNum * 3;
		}

	}
}