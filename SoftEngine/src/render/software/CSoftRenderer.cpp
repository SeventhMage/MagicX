#include "CSoftRenderer.h"
#include "base/seDef.h"
#include "../CRenderQueue.h"
#include "resource/IMaterialResource.h"
#include "CSoftEngine.h"
#include "CCPUBuffer.h"
#include "CSoftShaderProgram.h"
#include "math/CVector2.h"
#include "../STriangleMesh.h"
#include "../CRenderCell.h"

#include <algorithm>



namespace se
{
	namespace render
	{

		bool TriangleSort(const Triangle &t1, const Triangle &t2)
		{
			float z1 = (t1.vTranslatePosition[0].z + t1.vTranslatePosition[1].z + t1.vTranslatePosition[2].z) * 0.33333f;
			float z2 = (t1.vTranslatePosition[0].z + t1.vTranslatePosition[1].z + t1.vTranslatePosition[2].z) * 0.33333f;
			return (z1 < z2);
		}

		CSoftRenderer::CSoftRenderer()
			:m_pSoftRD(new CSoftRenderDriver())					
			, m_pRasterizer(new CRasterizer())
		{
			LoadMaterial();
		}

		CSoftRenderer::~CSoftRenderer()
		{
			SAFE_DEL(m_pSoftRD);
			SAFE_DEL(m_pRasterizer)
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
				(CSoftEngine::GetResourceManager()->LoadResource("material/materialgroup.mtl"));
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

		void CSoftRenderer::BufferData(uint bufferId, base::Vertices *pVertices, base::Indices *pIndices /* = nullptr */)
		{
			auto it = m_mapCPUBuffer.find(bufferId);
			if (it != m_mapCPUBuffer.end())
			{
				if (pVertices)
					it->second->BufferData(pVertices);
				if (pIndices)
					it->second->BufferData(pIndices);
			}
		}

		void CSoftRenderer::SubmitRenderCell(IRenderCell *pCell)
		{
			if (pCell)
			{
				uint materialId = pCell->GetMaterialID();
				if (m_renderQueueGroup.find(materialId) != m_renderQueueGroup.end())
				{
					IRenderQueue *pRenderQueue = m_renderQueueGroup[materialId];
					if (pRenderQueue)
					{
						pRenderQueue->AddRenderCell(pCell);
					}
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
			m_pSoftRD->Clear();
		}

		void CSoftRenderer::Render()
		{			
			for (auto mit = m_renderQueueGroup.begin(); mit != m_renderQueueGroup.end(); ++mit)
			{
				IRenderQueue *pRenderQueue = mit->second;
				if (pRenderQueue)
				{
					pRenderQueue->Render();
				}
			}
			Clear();
		}

		void CSoftRenderer::Render(IShaderProgram *pShaderProgram, uint materialId, uint bufferId, uint textureId)
		{
			if (!pShaderProgram)
				return;
			float *pViewMat = pShaderProgram->GetUniform(UN_VIEW_MAT);
			CMatrix4 viewMat;
			if (pViewMat)
			{				
				memcpy(viewMat.m, pViewMat, sizeof(viewMat.m));				
			}

			float *pModelMat = pShaderProgram->GetUniform(UN_MODEL_MAT);
			CMatrix4 modelMat;
			if (pModelMat)
			{
				memcpy(modelMat.m, pModelMat, sizeof(modelMat.m));
			}

			float *pWorldMat = pShaderProgram->GetUniform(UN_WORLD_MAT);
			CMatrix4 worldMat;
			if (pWorldMat)
			{
				memcpy(worldMat.m, pWorldMat, sizeof(worldMat.m));
			}

			CMatrix4 mwMat = modelMat * worldMat;

			IMaterial *pMaterial = CSoftEngine::GetMaterialManager()->GetMaterial(materialId);
			IBuffer *pBuffer = nullptr;
			auto bufferIt = m_mapCPUBuffer.find(bufferId);
			if (bufferIt != m_mapCPUBuffer.end())
				pBuffer = bufferIt->second;
			ITexture *pTexture = CSoftEngine::GetTextureManager()->GetTexture(textureId);

			if (pMaterial && pBuffer)
			{
				TriangleList triangleList;
				base::Vertices *pVertices = pBuffer->GetVertices();
				base::Indices *pIndices = pBuffer->GetIndices();
				
				SColor color = pMaterial->GetColor();

				if (pVertices)
				{
					Triangle triangle;
					

					if (pIndices)
					{			
						uint suffix = 0;
						uint indicesNum = pIndices->size / sizeof(ushort);
						for (uint i = 0; i < indicesNum; ++i)
						{
							ushort index = pIndices->pIndexData[i];
							if (index + 2 < pVertices->size)
							{
								triangle.vPosition[suffix].x = pVertices->pVertexData[3 * index];
								triangle.vPosition[suffix].y = pVertices->pVertexData[3 * index + 1];
								triangle.vPosition[suffix].z = pVertices->pVertexData[3 * index + 2];

								triangle.vertexColor[suffix] = color;

								if (suffix >= 2)
								{
									//转换到摄像机坐标
									for (int i = 0; i < 3; ++i)
									{
										mwMat.TransformVect(triangle.vTranslatePosition[i], triangle.vPosition[i]);
										mwMat.TransformVect(triangle.vTranslateNormal[i], triangle.vNormal[i]);
									}
									TranslateWorldToCamera(viewMat, triangle);

									if (!BackCulling(triangle)) //背面剔除
									{
										triangleList.push_back(triangle); //插入到三角形列表
									}
									triangle.Reset();
									suffix = 0;
								}
								else
								{
									++suffix;
								}

							}
							
						}
					}
					else
					{
						uint index = 0;
						for (uint i = 0; i < pVertices->count; ++i)
						{
							for (auto it = pVertices->format.begin(); it != pVertices->format.end(); ++it)
							{
								triangle.vertexAttr |= it->attribute;

								switch (it->attribute)
								{
								case base::VA_POSITION:
									triangle.vPosition[index].x = pVertices->pVertexData[i * pVertices->stride + it->offset];
									triangle.vPosition[index].y = pVertices->pVertexData[i * pVertices->stride + it->offset + 1];
									triangle.vPosition[index].z = pVertices->pVertexData[i * pVertices->stride + it->offset + 2];
								case base::VA_COLOR:
									triangle.vertexColor[index].r = color.r * pVertices->pVertexData[i * pVertices->stride + it->offset];
									triangle.vertexColor[index].g = color.g * pVertices->pVertexData[i * pVertices->stride + it->offset + 1];
									triangle.vertexColor[index].b = color.b * pVertices->pVertexData[i * pVertices->stride + it->offset + 2];
								case base::VA_TEXCOORD:
									triangle.vTexCoord[index].x = pVertices->pVertexData[i * pVertices->stride + it->offset];
									triangle.vTexCoord[index].y = pVertices->pVertexData[i * pVertices->stride + it->offset + 1];
								case base::VA_NORMAL:
									triangle.vNormal[index].x = pVertices->pVertexData[i * pVertices->stride + it->offset];
									triangle.vNormal[index].y = pVertices->pVertexData[i * pVertices->stride + it->offset + 1];
									triangle.vNormal[index].z = pVertices->pVertexData[i * pVertices->stride + it->offset + 2];
								default:
									break;
								}
							}
							if (index >= 2)
							{
								//转换到摄像机坐标
								TranslateWorldToCamera(viewMat, triangle);

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
					}
					

					//对三角形列表渲染											

					//排序
					std::sort(triangleList.begin(), triangleList.end(), TriangleSort);					

					float pLight[] = {100, 100, 100}; //pShaderProgram->GetUniform(UN_LIGHT_POS);
					if (pLight)
					{
						CVector3 vLightPos;
						memcpy(vLightPos.v, pLight, sizeof(vLightPos.v));
						//顶点级别光照计算
						VertexLightCalc(vLightPos, viewMat, triangleList);
					}


					//转换到屏幕坐标
					float *pProjMat = pShaderProgram->GetUniform(UN_PROJ_MAT);
					if (pProjMat)
					{
						CMatrix4 projMat;
						memcpy(projMat.m, pProjMat, sizeof(projMat.m));
						TranslateCameraToScreen(projMat, triangleList);
					}					

					//光栅化
					for (auto it = triangleList.begin(); it != triangleList.end(); ++it)
					{
						//base::LogPrint("x:%f, y:%f, z:%f  x:%f, y:%f, z%f  x:%f, y:%f, z%f\n",
						//	it->vTranslatePosition[0].x, it->vTranslatePosition[0].y, it->vTranslatePosition[0].z,
						//	it->vTranslatePosition[1].x, it->vTranslatePosition[1].y, it->vTranslatePosition[1].z,
						//	it->vTranslatePosition[2].x, it->vTranslatePosition[2].y, it->vTranslatePosition[2].z);

						m_pRasterizer->SetDrawBuffer(m_pSoftRD->GetDrawBuffer());
						m_pRasterizer->SetBufferSize(m_pSoftRD->GetBufferWidth(), m_pSoftRD->GetBufferHeight());
						m_pRasterizer->DrawTriangle(*it);
					}
					//输出到设备
					m_pSoftRD->DrawBuffer();
					
				}
			}
		}

		void CSoftRenderer::TranslateWorldToCamera(const CMatrix4 &viewMat, Triangle &triangle)
		{					
			for (int i = 0; i < 3; ++i)
			{
				CVector3 in = triangle.vTranslatePosition[i];
				viewMat.TransformVect(triangle.vTranslatePosition[i], in);
				CVector3 inn = triangle.vTranslateNormal[i];
				viewMat.TransformVect(triangle.vTranslateNormal[i], inn);
				triangle.vTranslateNormal[i].normalize();
			}
			
			//////////////////////////////////////////////////////////////////////////
			//temp
			for (int i = 0; i < 3; ++i)
			{
				triangle.vTranslateNormal[i] = triangle.vTranslatePosition[0].crossProduct(triangle.vTranslatePosition[1]);
				triangle.vTranslateNormal[i].normalize();
			}
		}

		void CSoftRenderer::TranslateCameraToScreen(const CMatrix4 &projMat, TriangleList &triList)
		{
			float width = (0.5f * 2 - 0.5f);
			float height = (0.5f * 2 - 0.5f);

			for (auto it = triList.begin(); it != triList.end(); ++it)
			{
				for (int i = 0; i < 3; ++i)
				{
					CVector3 in = it->vTranslatePosition[i];
					projMat.TransformVect(it->vTranslatePosition[i], in);
					float z = fabs(it->vTranslatePosition[i].z);
					it->vTranslatePosition[i].x /= z;
					it->vTranslatePosition[i].y /= z;

					it->vTranslatePosition[i].x += width;
					it->vTranslatePosition[i].y = height - it->vTranslatePosition[i].y;

					it->vTranslatePosition[i].x *= m_pSoftRD->GetBufferWidth();
					it->vTranslatePosition[i].y *= m_pSoftRD->GetBufferHeight();
				}
			}
		}

		bool CSoftRenderer::BackCulling(const Triangle &triangle)
		{						
			CVector3 v0 = triangle.vTranslatePosition[1] - triangle.vTranslatePosition[0];
			CVector3 v1 = triangle.vTranslatePosition[2] - triangle.vTranslatePosition[1];
			CVector3 vNormal = v0.crossProduct(v1);
			CVector3 vCamDir(0, 0, -1);
			return (vNormal.dotProduct(vCamDir) > 0);
 		}

		void CSoftRenderer::VertexLightCalc(const CVector3 &lightPos, const CMatrix4 &viewMat, TriangleList &triList)
		{
			CVector3 viewLightPos;
			viewMat.TransformVect(viewLightPos, lightPos);
			for (auto it = triList.begin(); it != triList.end(); ++it)
			{
				for (int i = 0; i < 3; ++i)
				{
					float dot = (viewLightPos - it->vTranslatePosition[i]).normalize().dotProduct(it->vTranslateNormal[i]);
					if (dot < 0)
						dot = 0;
					it->vertexColor[i] *= dot;
				}				
			}
		}

		IShaderProgram * CSoftRenderer::CreateShaderProgram()
		{
			return new CSoftShaderProgram();
		}

		void CSoftRenderer::DestroyShaderProgram(IShaderProgram *pShaderProgram)
		{
			SAFE_DEL(pShaderProgram);
		}

		IRenderCell * CSoftRenderer::CreateRenderCell(uint bufferId, uint materialId, uint textureId)
		{
			return new CRenderCell(bufferId, materialId, textureId);
		}

		void CSoftRenderer::DestroyRenderCell(IRenderCell *pCell)
		{
			SAFE_DEL(pCell);
		}

	}
}