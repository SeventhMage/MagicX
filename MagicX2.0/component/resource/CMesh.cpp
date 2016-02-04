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

		void CMesh::Update(uint deltaTime, const CMatrix4 &mat4VP)
		{
			for (uint i = 0; i < m_uTriangleNum; ++i)
			{
				if (m_pRenderableObject[i])
				{
					render::IShaderProgram *shaderProgram = m_pRenderableObject[i]->GetShaderProgram();
					if (shaderProgram)
					{
						CMatrix4 modelMat4;
						modelMat4.setTranslation(CVector3(0, 20.0f, 0));
						CMatrix4 mat4 = mat4VP * modelMat4;
						shaderProgram->SetUniform("mvpMatrix", &mat4.m);
					}

					IBufferObject *bufferObject = m_pRenderableObject[i]->GetVertexBufferObject();
					if (bufferObject)
					{
						bufferObject->BufferData(m_pvLocalList, sizeof(CVector3)* m_uVerticesNum);
					}
				}
			}
		}

		void CMesh::CreatePLXRenderable(uint idx)
		{
			m_pRenderableObject.insert(m_pRenderableObject.end(), m_pGPUBuffer->CreateRenderableObject());
			if (m_pRenderableObject[idx])
			{							
				render::IShaderProgram *shaderProgram = m_pRenderableObject[idx]->GetShaderProgram();
				if (shaderProgram)
				{
					shaderProgram->CreateStandShader(ESS_SHADER_FLAT);
					
					SColor color(m_pTriangleList[idx].color);
					float fColor[] = { color.GetRed() / 255.0f, color.GetGreen() / 255.0f, color.GetBlue() / 255.0f, color.GetAlpha() / 255.0f};
					shaderProgram->SetUniform("vColor", fColor);
				}
				
				m_pGPUBuffer->Begin();
				m_pRenderableObject[idx]->CreateVertexBufferObject(m_pvLocalList, sizeof(CVector3)* m_uVerticesNum, 0, m_uVerticesNum, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pRenderableObject[idx]->CreateIndexBufferObject(m_pTriangleList[idx].indices, 3, RVT_UINT, m_uVerticesNum, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				m_pGPUBuffer->EnableVertexAttrib(VAL_POSITION, 3, RVT_FLOAT, sizeof(CVector3), 0);
				m_pGPUBuffer->End();
			}
		}

	}
}