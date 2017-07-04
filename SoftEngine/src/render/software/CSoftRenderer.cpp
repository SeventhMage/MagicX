#include "CSoftRenderer.h"
#include "base/seDef.h"
#include "../CRenderQueue.h"
#include "resource/IMaterialResource.h"
#include "CSoftEngine.h"
#include "CCPUBuffer.h"
#include "math/CVector2.h"
#include "../STriangleMesh.h"
#include "CRasterizer.h"

#include <algorithm>

namespace se
{
	namespace render
	{
		CSoftRenderer::CSoftRenderer()
			:m_pSoftRD(new CSoftRenderDriver())					
		{
			LoadMaterial();
		}

		CSoftRenderer::~CSoftRenderer()
		{
			SAFE_DEL(m_pSoftRD);
			for (auto it = m_renderQueueGroup.begin(); it != m_renderQueueGroup.end(); ++it)
			{
				SAFE_DEL(it->second);
			}

			for (auto it = m_mapCPUBuffer.begin(); it != m_mapCPUBuffer.end(); ++it)
			{
				SAFE_DEL(it->second);
			}
		}

		void CSoftRenderer::LoadMaterial()
		{
			m_renderQueueGroup.clear();
			resource::IMaterialResource *pResource = dynamic_cast<resource::IMaterialResource *>
				(CSoftEngine::GetResourceManager()->LoadResource("materialgroup.mtl"));
			if (pResource)
			{
				for (int i = 0; i < pResource->GetAttrCount(); ++i)
				{
					std::string materialName = pResource->GetValueByIdx(i);
					resource::IMaterialResource *pMaterialRes = dynamic_cast<resource::IMaterialResource *>
						(CSoftEngine::GetResourceManager()->LoadResource(materialName.c_str()));
					render::IRenderQueue *pRenderQueue = new CRenderQueue(materialName.c_str());
					m_renderQueueGroup[pRenderQueue->GetMaterialID()] = pRenderQueue;
				}
				CSoftEngine::GetResourceManager()->ReleaseResource(pResource);
			}
		}

		uint CSoftRenderer::CreateBuffer()
		{
			uint id = m_mapCPUBuffer.size() + 1;
			IBuffer *pBuffer = new CCPUBuffer(id);
			m_mapCPUBuffer[id] = pBuffer;
			return id;
		}

		void CSoftRenderer::DestroyBuffer(uint bufferId)
		{
			auto it = m_mapCPUBuffer.find(bufferId);
			if (it != m_mapCPUBuffer.end())
			{
				IBuffer *pBuffer = m_mapCPUBuffer[bufferId];				
				m_mapCPUBuffer.erase(it);
				SAFE_DEL(pBuffer);
			}
		}

		void CSoftRenderer::BufferData(uint bufferId, ubyte *vertices, /*顶点数据 */ 
			uint vertSize, /*顶点数据尺寸 */ int count, /*顶点数量 */ VertexFormat format, /*顶点属性格式 */ 
			ubyte *indices, /*索引数据 */ uint indicesSize /*索引数据尺寸 */)
		{
			if (m_mapCPUBuffer.find(bufferId) != m_mapCPUBuffer.end())
			{

			}
		}



		void CSoftRenderer::UpdateUniform(EUniformName name, ubyte *data, uint size)
		{
			switch (name)
			{
			case UN_MODEL_MAT:
				break;
			case UN_WORLD_MAT:
				break;
			case UN_VIEW_MAT:
				memcpy(m_viewMatrix.m, data, size);
				break;
			case UN_PROJ_MAT:
				memcpy(m_projMatrix.m, data, size);
				break;						
			case UN_CAM_POS:
				memcpy(m_cameraPos.v, data, size);
				break;
			default:
				break;
			}
		}

		void CSoftRenderer::SubmitRenderCell(IRenderCell *pCell)
		{
			if (pCell)
			{
				uint materialId = pCell->GetMaterialID();
				IRenderQueue *pRenderQueue = m_renderQueueGroup[materialId];
				if (pRenderQueue)
				{
					pRenderQueue->AddRenderCell(pCell);
				}				
			}			
		}

		void CSoftRenderer::Clear()
		{
			for (auto mit = m_renderQueueGroup.begin(); mit != m_renderQueueGroup.end(); ++mit)
			{
				IRenderQueue *pRenderQueue = mit->second;
				if (pRenderQueue)
				{
					pRenderQueue->Clear();
				}				
			}
		}

		void CSoftRenderer::Render()
		{
			Clear();
			for (auto mit = m_renderQueueGroup.begin(); mit != m_renderQueueGroup.end(); ++mit)
			{
				IRenderQueue *pRenderQueue = mit->second;
				if (pRenderQueue)
				{
					pRenderQueue->Render();
				}
			}
		}

		void CSoftRenderer::Render(uint materialId, uint bufferId, uint textureId)
		{
			IMaterial *pMaterial = CSoftEngine::GetMaterialManager()->GetMaterial(materialId);
			IBuffer *pBuffer = nullptr;
			auto bufferIt = m_mapCPUBuffer.find(bufferId);
			if (bufferIt != m_mapCPUBuffer.end())
				pBuffer = bufferIt->second;
			ITexture *pTexture = CSoftEngine::GetTextureManager()->GetTexture(textureId);

			if (pMaterial && pBuffer && pTexture)
			{
				TriangleList triangleList;
				Vertices *pVertices = pBuffer->GetVertices();
				if (pVertices)
				{
					Triangle triangle;
					uint index = 0;
					
					for (uint i = 0; i < pVertices->count; ++i)
					{
						for (auto it = pVertices->format.begin(); it != pVertices->format.end(); ++it)
						{
							triangle.vertexAttr |= it->attribute;

							switch (it->attribute)
							{
							case VA_POSITION:
								triangle.vPosition[index].x = pVertices->pVertexData[i * pVertices->stride + it->offset];
								triangle.vPosition[index].y = pVertices->pVertexData[i * pVertices->stride + it->offset + 1];
								triangle.vPosition[index].z = pVertices->pVertexData[i * pVertices->stride + it->offset + 2];
							case VA_COLOR:
								triangle.vertexColor[index].r = pVertices->pVertexData[i * pVertices->stride + it->offset];
								triangle.vertexColor[index].g = pVertices->pVertexData[i * pVertices->stride + it->offset + 1];
								triangle.vertexColor[index].b = pVertices->pVertexData[i * pVertices->stride + it->offset + 2];
							case VA_TEXCOORD:
								triangle.vTexCoord[index].x = pVertices->pVertexData[i * pVertices->stride + it->offset];
								triangle.vTexCoord[index].y = pVertices->pVertexData[i * pVertices->stride + it->offset + 1];
							case VA_NORMAL:
								triangle.vNormal[index].x = pVertices->pVertexData[i * pVertices->stride + it->offset];
								triangle.vNormal[index].y = pVertices->pVertexData[i * pVertices->stride + it->offset + 1];
								triangle.vNormal[index].z = pVertices->pVertexData[i * pVertices->stride + it->offset + 2];
							default:
								break;
							}
						}
						if (index >= 2)
						{			
							if (!BackCulling(triangle)) //背面剔除
							{
								triangleList.push_back(triangle); //插入到三角形列表
							}
							triangle.Reset();
							index = 0;
						}
						else
						{
							++index;
						}
					}

					//对三角形列表渲染
					
					//转换到摄像机坐标
					TranslateWorldToCamera(triangleList);

					//排序
					std::sort(triangleList.begin(), triangleList.end(), TriangleSort);

					//顶点级别光照计算
					VertexLightCalc(triangleList);

					//转换到屏幕坐标
					TranslateCameraToScreen(triangleList);

					//光栅化
					CRasterizer::DrawTriangle(m_pSoftRD->GetDrawBuffer(), m_pSoftRD->GetBufferWidth(), 
						m_pSoftRD->GetBufferHeight(), triangle);

					//输出到设备
					m_pSoftRD->DrawBuffer();
					
				}
			}
		}

		void CSoftRenderer::TranslateWorldToCamera(TriangleList &triList)
		{			
			for (auto it = triList.begin(); it != triList.end(); ++it)
			{
				for (int i = 1; i < 3; ++i)
				{					
					m_viewMatrix.TransformVect(it->vTranslatePosition[i], it->vPosition[i]);
				}
			}
		}

		void CSoftRenderer::TranslateCameraToScreen(TriangleList &triList)
		{
			float width = (0.5 * m_pSoftRD->GetBufferWidth() - 0.5);
			float height = (0.5 * m_pSoftRD->GetBufferHeight() - 0.5);

			for (auto it = triList.begin(); it != triList.end(); ++it)
			{
				for (int i = 1; i < 3; ++i)
				{
					m_projMatrix.TransformVect(it->vTranslatePosition[i], it->vPosition[i]);
					it->vTranslatePosition[i].x /= it->vTranslatePosition[i].z;
					it->vTranslatePosition[i].y /= it->vTranslatePosition[i].z;

					it->vTranslatePosition[i].x += width;
					it->vTranslatePosition[i].y = height - it->vTranslatePosition[i].y;
				}
			}
		}

		bool CSoftRenderer::BackCulling(const Triangle &triangle)
		{						
			CVector3 v0 = triangle.vPosition[1] - triangle.vPosition[0];
			CVector3 v1 = triangle.vPosition[2] - triangle.vPosition[1];
			CVector3 vNormal = v0.crossProduct(v1);
			CVector3 vCamDir = m_cameraPos - triangle.vPosition[0];
			return (vNormal.dotProduct(vCamDir) > 0);
 		}

		bool CSoftRenderer::TriangleSort(const Triangle &t1, const Triangle &t2)
		{
			float z1 = (t1.vTranslatePosition[0].z + t1.vTranslatePosition[1].z + t1.vTranslatePosition[2].z) * 0.33333;
			float z2 = (t1.vTranslatePosition[0].z + t1.vTranslatePosition[1].z + t1.vTranslatePosition[2].z) * 0.33333;
			return (z1 < z2);
		}

		void CSoftRenderer::VertexLightCalc(TriangleList &triList)
		{
			
		}

	}
}