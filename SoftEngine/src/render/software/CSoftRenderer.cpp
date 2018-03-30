#include <algorithm>

#include "CSoftRenderer.h"
#include "base/seDef.h"
#include "base/Log.h"
#include "resource/IMaterialResource.h"
#include "CSoftEngine.h"
#include "CCPUBuffer.h"
#include "CSoftShaderProgram.h"
#include "math/CVector2.h"
#include "CIlluminationRender.h"
#include "CSoftVertexArrayObject.h"
#include "../STriangleMesh.h"
#include "../CRenderCell.h"
#include "../CRenderQueue.h"
#include "CSoftShaderAttribute.h"


namespace se
{
	namespace render
	{

		class CalcFragment_1 : public CalcFragmentFunc
		{
		public:
			CalcFragment_1(CSoftFragmentShader *pShader)
				:m_pShader(pShader)
			{

			}
			virtual Color operator()(const FragmentParam &param) const
			{
				const FragmentParam_1 &p = dynamic_cast<const FragmentParam_1 &>(param);
				if (m_pShader)
				{
					static CSoftShaderAttribute inAttr;
					inAttr.SetAttribute(base::VA_COLOR, p.color.c, sizeof(p.color.c));
					return m_pShader->Process(inAttr);
				}

				return p.color;
			}
		private:
			CSoftFragmentShader *m_pShader;
		};


		class CalcFragment_2 : public CalcFragmentFunc
		{
		public:
			CalcFragment_2(CSoftFragmentShader *pShader)
				:m_pShader(pShader)
			{

			}
			virtual Color operator()(const FragmentParam &param) const
			{
				const FragmentParam_2 &p = dynamic_cast<const FragmentParam_2 &>(param);

				if (m_pShader)
				{
					static CSoftShaderAttribute inAttr;
					inAttr.SetAttribute(base::VA_COLOR, p.color.c, sizeof(p.color.c));
					inAttr.SetAttribute(base::VA_TEXCOORD, p.texCoord.v, sizeof(p.texCoord.v));
					return m_pShader->Process(inAttr);
				}

				return p.color;
			}
		private:
			CSoftFragmentShader *m_pShader;
		};

		bool TriangleSort(const Triangle &t1, const Triangle &t2)
		{
			float z1 = (t1.vTranslatePosition[0].z + t1.vTranslatePosition[1].z + t1.vTranslatePosition[2].z) * 0.33333f;
			float z2 = (t1.vTranslatePosition[0].z + t1.vTranslatePosition[1].z + t1.vTranslatePosition[2].z) * 0.33333f;
			return (z1 < z2);
		}

		CSoftRenderer::CSoftRenderer()
			:m_pSoftRD(new CSoftRenderDriver())					
			, m_pRasterizer(new CRasterizer())
			, m_shaderProgramId(0)
			, m_vaoId(0)
			, m_bufferId(0)
			, m_textureId(0)
		{						
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

			for (auto it = m_mapShaderProgram.begin(); it != m_mapShaderProgram.end(); ++it)
			{
				SAFE_DEL(it->second);
			}

			for (auto it = m_mapVAOs.begin(); it != m_mapVAOs.end(); ++it)
			{
				SAFE_DEL(it->second);
			}

		}

		void CSoftRenderer::Init()
		{
			LoadMaterial();
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
					IMaterial *pMaterial = CSoftEngine::GetMaterialManager()->CreateMaterial(materialName.c_str());
					render::IRenderQueue *pRenderQueue = new CRenderQueue(pMaterial);
					m_renderQueueGroup[pMaterial->GetID()] = pRenderQueue;
				}
				CSoftEngine::GetResourceManager()->ReleaseResource(pResource);
			}
		}


		uint CSoftRenderer::CreateVAO()
		{
			uint id = m_mapVAOs.size() + 1;
			IVertexArrayObject *pVAO = new CSoftVertexArrayObject(id);
			m_mapVAOs[id] = pVAO;

			return id;
		}

		void CSoftRenderer::DestroyVAO(uint vaoId)
		{
			auto it = m_mapVAOs.find(vaoId);
			if (it != m_mapVAOs.end())
			{
				delete it->second;
				m_mapVAOs.erase(it);
			}
		}

		void CSoftRenderer::VertexAttrPointer(uint vaoId, uint index, uint size, EDataType type, uint stride, uint offset)
		{
			auto it = m_mapVAOs.find(vaoId);
			if (it != m_mapVAOs.end())
			{
				it->second->VertexAttrPointer(index, size, type, stride, offset);
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
					scene::IScene *pScene = CSoftEngine::GetSceneManager()->GetCurrentScene();
					if (pScene)
					{
						scene::ICamera *pCamera = pScene->GetCamera();
						if (pCamera)
						{
							pRenderQueue->Render(pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix());
						}
					}
				}
			}

			//输出到设备
			m_pSoftRD->DrawBuffer();

			Clear();
		}

		void CSoftRenderer::TranslateWorldToCamera(const CMatrix4 &viewMat, Triangle &triangle)
		{					
			CMatrix4 norMat = viewMat;
			norMat.SetTranslation(CVector3(0, 0, 0));
			for (int i = 0; i < 3; ++i)
			{
				CVector4 in = triangle.vTranslatePosition[i];
				viewMat.TransformVect(triangle.vTranslatePosition[i], in);
				CVector3 inn = triangle.vTranslateNormal[i];				
				norMat.TransformVect(triangle.vTranslateNormal[i], inn);
				triangle.vTranslateNormal[i].normalize();
			}		
		}

		void CSoftRenderer::TranslateCameraToScreen(const CMatrix4 &projMat, TriangleList &triList)
		{
			for (auto it = triList.begin(); it != triList.end(); ++it)
			{
				for (int i = 0; i < 3; ++i)
				{
					CVector4 in = it->vTranslatePosition[i];					
					
					projMat.TransformVect(it->vTranslatePosition[i], in);
					float invW = 1.0f / it->vTranslatePosition[i].w;
					it->vTranslatePosition[i].x *= invW;
					it->vTranslatePosition[i].y *= invW;
					it->vTranslatePosition[i].z *= invW;

					it->vTranslatePosition[i].x = (it->vTranslatePosition[i].x + 1.0f) * 0.5f * m_pSoftRD->GetBufferWidth();
					it->vTranslatePosition[i].y = (1 - it->vTranslatePosition[i].y) * 0.5f * m_pSoftRD->GetBufferHeight();
				}
			}
		}

		bool CSoftRenderer::BackCulling(const Triangle &triangle)
		{			
			CVector3 v0 = CVector3(triangle.vTranslatePosition[1].x, triangle.vTranslatePosition[1].y, triangle.vTranslatePosition[1].z) 
				- CVector3(triangle.vTranslatePosition[0].x, triangle.vTranslatePosition[0].y, triangle.vTranslatePosition[0].z);
			CVector3 v1 = CVector3(triangle.vTranslatePosition[2].x, triangle.vTranslatePosition[2].y, triangle.vTranslatePosition[2].z)
				- CVector3(triangle.vTranslatePosition[0].x, triangle.vTranslatePosition[0].y, triangle.vTranslatePosition[0].z);
			CVector3 vNormal = v0.crossProduct(v1);
			CVector3 vCamDir(0, 0, -1);
			return (vNormal.dotProduct(vCamDir) > 0);
 		}

		void CSoftRenderer::VertexLightCalc(const CVector3 &lightPos, const CMatrix4 &viewMat, TriangleList &triList)
		{
            CIlluminationRender illumination(SColor(1.f, 0.4f, 0.4f, 0.4f), SColor(1.f, 0.8f, 0.8f, 0.8f), SColor(1.f, 1.f, 1.f, 1.f));
			CVector3 viewLightPos;
			viewMat.TransformVect(viewLightPos, lightPos);
			for (auto it = triList.begin(); it != triList.end(); ++it)
			{
				for (int i = 0; i < 3; ++i)
				{
                    CVector3 lightDir = viewLightPos - CVector3(it->vTranslatePosition[i].x, it->vTranslatePosition[i].y,
                                            it->vTranslatePosition[i].z).normalize();
                    lightDir.normalize();
                    it->vertexColor[i] = illumination.Calculate(it->vertexColor[i], lightDir, CVector3(0, 0, 1), it->vTranslateNormal[i], 1.f, 1.f, 1.f, 80.f, viewLightPos.getDistanceFrom(CVector3(it->vTranslatePosition[i].x, it->vTranslatePosition[i].y, it->vTranslatePosition[i].z)));
				}				
			}
		}

		uint CSoftRenderer::CreateShaderProgram()
		{
			uint id = m_mapShaderProgram.size() + 1;

			m_mapShaderProgram[id] = new CSoftShaderProgram(id);

			return id;
		}

		void CSoftRenderer::DestroyShaderProgram(uint id)
		{
			auto it = m_mapShaderProgram.find(id);
			if (it != m_mapShaderProgram.end())
			{
				delete it->second;
				m_mapShaderProgram.erase(it);
			}
		}

		IShaderProgram * CSoftRenderer::GetShaderProgram(uint shaderProgramId) const
		{
			auto it = m_mapShaderProgram.find(shaderProgramId);
			if (it != m_mapShaderProgram.end())
			{
				return it->second;
			}
			return nullptr;
		}


		IRenderCell * CSoftRenderer::CreateRenderCell(uint bufferId, uint materialId, uint textureId)
		{
			return new CRenderCell(bufferId, materialId, textureId);
		}

		void CSoftRenderer::DestroyRenderCell(IRenderCell *pCell)
		{
			SAFE_DEL(pCell);
		}


		void CSoftRenderer::UseShaderProgram(uint shaderProgramId)
		{
			m_shaderProgramId = shaderProgramId;
		}

		void CSoftRenderer::EnableVertexArrayObject(uint vaoId)
		{
			m_vaoId = vaoId;
		}

		void CSoftRenderer::BindBuffer(uint bufferId)
		{
			m_bufferId = bufferId;
		}

		void CSoftRenderer::BindTexture(uint textureId)
		{
			m_textureId = textureId;
		}

		void CSoftRenderer::DrawElements()
		{
			CSoftShaderProgram *pShaderProgram = nullptr;
			IBuffer *pBuffer = nullptr;
			ITexture *pTexture = nullptr;

			auto shaderIt = m_mapShaderProgram.find(m_shaderProgramId);
			if (shaderIt != m_mapShaderProgram.end())
			{
				pShaderProgram = static_cast<CSoftShaderProgram *>(shaderIt->second);
				if (!pShaderProgram)
				{
					base::LogPrint("ShaderProgram is nullptr");
					return;
				}
			}

			auto buffIt = m_mapCPUBuffer.find(m_bufferId);
			if (buffIt != m_mapCPUBuffer.end())
			{
				pBuffer = buffIt->second;
				if (!pBuffer)
				{
					base::LogPrint("bufffer is nullptr");
					return;
				}
			}

			if (m_textureId > 0)
				pTexture = CSoftEngine::GetTextureManager()->GetTexture(m_textureId);

			float *pViewMat = (float *)pShaderProgram->GetUniform(UN_VIEW_MAT);
			CMatrix4 viewMat;
			if (pViewMat)
			{
				memcpy(viewMat.m, pViewMat, sizeof(viewMat.m));
			}

			float *pWorldMat = (float *)pShaderProgram->GetUniform(UN_WORLD_MAT);
			CMatrix4 worldMat;
			if (pWorldMat)
			{
				memcpy(worldMat.m, pWorldMat, sizeof(worldMat.m));
			}

			CMatrix4 mwMat = worldMat;
			CMatrix4 temp;
			mwMat.GetInverse(temp);
			CMatrix4 mwNormalMat;
			temp.GetTransposed(mwNormalMat);
			mwNormalMat.SetTranslation(CVector3(0, 0, 0));
						
			if (pBuffer)
			{
				TriangleList triangleList;
				base::Vertices *pVertices = pBuffer->GetVertices();
				base::Indices *pIndices = pBuffer->GetIndices();
				
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
								triangle.vPosition[suffix].x = *(float *)(pVertices->pVertexData + sizeof(CVector3) * index);
								triangle.vPosition[suffix].y = *(float *)(pVertices->pVertexData + sizeof(CVector3)* index + 1 * sizeof(float));
								triangle.vPosition[suffix].z = *(float *)(pVertices->pVertexData + sizeof(CVector3)* index + 2 * sizeof(float));

								for (uint j = 0; j < pVertices->format.size(); ++j)
								{
									if (pVertices->format[j].attribute == base::VA_NORMAL)
									{
										triangle.vNormal[suffix].x = *(float *)(pVertices->pVertexData + pVertices->format[j].offset + sizeof(CVector3)* index);
										triangle.vNormal[suffix].y = *(float *)(pVertices->pVertexData + pVertices->format[j].offset + sizeof(CVector3)* index + 1 * sizeof(float));
										triangle.vNormal[suffix].z = *(float *)(pVertices->pVertexData + pVertices->format[j].offset + sizeof(CVector3)* index + 2 * sizeof(float));
									}
									else if (pVertices->format[j].attribute == base::VA_TEXCOORD)
									{
										triangle.vTexCoord[suffix].x = *(float *)(pVertices->pVertexData + pVertices->format[j].offset + sizeof(CVector2)* index);
										triangle.vTexCoord[suffix].y = *(float *)(pVertices->pVertexData + pVertices->format[j].offset + sizeof(CVector2)* index + 1 * sizeof(float));
									}
								}

								triangle.vertexColor[suffix] = Color(1, 1, 1, 1);

								CSoftShaderAttribute outAttr;
								CSoftVertexShader *pVertexShader = pShaderProgram->GetVertexShader();
								if (pVertexShader)
								{
									const CSoftShaderProgram::UniformMap &uniformMap = pShaderProgram->GetAllUniform();
									for (auto it = uniformMap.begin(); it != uniformMap.end(); ++it)
									{
										pVertexShader->SetUniform(it->first, it->second.data);
									}

									//Input the attribute.
									CSoftShaderAttribute inAttr;									
									inAttr.SetAttribute(base::VA_POSITION, triangle.vPosition[suffix].v, sizeof(triangle.vPosition[suffix].v));
									inAttr.SetAttribute(base::VA_NORMAL, triangle.vNormal[suffix].v, sizeof(triangle.vNormal[suffix].v));
									inAttr.SetAttribute(base::VA_COLOR, triangle.vertexColor[suffix].c, sizeof(triangle.vertexColor[suffix].c));
									inAttr.SetAttribute(base::VA_TEXCOORD, triangle.vTexCoord[suffix].v, sizeof(triangle.vTexCoord[suffix].v));

									//Excute the vertex shader.
									triangle.vTranslatePosition[suffix] = pVertexShader->Process(inAttr, outAttr);

									//Deal with the output postion.
									float invW = 1.0f / triangle.vTranslatePosition[suffix].w;
									triangle.vTranslatePosition[suffix].x *= invW;
									triangle.vTranslatePosition[suffix].y *= invW;
									triangle.vTranslatePosition[suffix].z *= invW;

									triangle.vTranslatePosition[suffix].x = (triangle.vTranslatePosition[suffix].x + 1.0f) * 0.5f * m_pSoftRD->GetBufferWidth();
									triangle.vTranslatePosition[suffix].y = (1 - triangle.vTranslatePosition[suffix].y) * 0.5f * m_pSoftRD->GetBufferHeight();

									//Output the attribute.
									memcpy(triangle.vTranslateNormal[suffix].v, outAttr.GetAttribute(base::VA_NORMAL).data, sizeof(triangle.vTranslateNormal[suffix].v));
									memcpy(triangle.vertexColor[suffix].c, outAttr.GetAttribute(base::VA_COLOR).data, sizeof(triangle.vertexColor[suffix].c));
									memcpy(triangle.vTexCoord[suffix].v, outAttr.GetAttribute(base::VA_TEXCOORD).data, sizeof(triangle.vTexCoord[suffix].v));
								}

								if (suffix >= 2)
								{
									for (int i = 0; i < 3; ++i)
									{
									//	mwMat.TransformVect(triangle.vTranslatePosition[i], triangle.vPosition[i]);
									//	mwNormalMat.TransformVect(triangle.vTranslateNormal[i], triangle.vNormal[i]);
									}

									//转换到摄像机坐标
//									TranslateWorldToCamera(viewMat, triangle);

	//								if (!BackCulling(triangle)) //背面剔除
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
						Color color(1, 1, 0, 0);
						uint index = 0;
						for (uint i = 0; i < pVertices->count; ++i)
						{
							for (auto it = pVertices->format.begin(); it != pVertices->format.end(); ++it)
							{
								triangle.vertexAttr |= it->attribute;

								switch (it->attribute)
								{
								case base::VA_POSITION:
									triangle.vPosition[index].x = ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset];
									triangle.vPosition[index].y = ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 1];
									triangle.vPosition[index].z = ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 2];
								case base::VA_COLOR:
									triangle.vertexColor[index].r = color.r * ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset];
									triangle.vertexColor[index].g = color.g * ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 1];
									triangle.vertexColor[index].b = color.b * ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 2];
								case base::VA_TEXCOORD:
									triangle.vTexCoord[index].x = ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset];
									triangle.vTexCoord[index].y = ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 1];
								case base::VA_NORMAL:
									triangle.vNormal[index].x = ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset];
									triangle.vNormal[index].y = ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 1];
									triangle.vNormal[index].z = ((float*)pVertices->pVertexData)[i * pVertices->stride + it->offset + 2];
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
					//std::sort(triangleList.begin(), triangleList.end(), TriangleSort);

					float pLight[] = { 100, 100, 100 }; //pShaderProgram->GetUniform(UN_LIGHT_POS);
					//if (pLight)
					{
						CVector3 vLightPos;
						memcpy(vLightPos.v, pLight, sizeof(vLightPos.v));
						//顶点级别光照计算
						//VertexLightCalc(vLightPos, viewMat, triangleList);
					}


					//转换到屏幕坐标
					//float *pProjMat = (float *)pShaderProgram->GetUniform(UN_PROJ_MAT);
					//if (pProjMat)
					//{
					//	CMatrix4 projMat;
					//	memcpy(projMat.m, pProjMat, sizeof(projMat.m));
					//	TranslateCameraToScreen(projMat, triangleList);
					//}

					//光栅化

					CSoftFragmentShader *pFragmentShader = pShaderProgram->GetFragmentShader();
					if (pFragmentShader)
					{
						pFragmentShader->SetUniform(UN_TEXTURE_0, (ubyte *)&m_textureId);
					}

					for (auto it = triangleList.begin(); it != triangleList.end(); ++it)
					{
						m_pRasterizer->SetDrawBuffer(m_pSoftRD->GetDrawBuffer(), m_pSoftRD->GetBufferWidth(), m_pSoftRD->GetBufferHeight());
						m_pRasterizer->SetDepthBuffer(m_pSoftRD->GetDepthBuffer());
						if (pTexture)
						{
							m_pRasterizer->SetTextureInfo(pTexture->GetData(), pTexture->GetWidth(), pTexture->GetHeight());
							m_pRasterizer->BindFragmentFunc(CalcFragment_2(pFragmentShader));
						}
						else
						{							
							m_pRasterizer->SetTextureInfo(nullptr, 0, 0);
							m_pRasterizer->BindFragmentFunc(CalcFragment_1(pFragmentShader));
						}						
						m_pRasterizer->DrawTriangle(*it);
					}
				}
			}
		}
	}

}
