#include "CSoftRenderer.h"
#include "base/seDef.h"
#include "../CRenderQueue.h"
#include "resource/IMaterialResource.h"
#include "CSoftEngine.h"
#include "CCPUBuffer.h"
#include "math/CVector2.h"

namespace se
{
	namespace render
	{
		CSoftRenderer::CSoftRenderer()
			:m_pSoftRD(new CSoftRenderDriver())
			, m_renderAddr(nullptr)
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



		void CSoftRenderer::UpdateUniform(EUniform type, EUniformName name, ubyte *data, uint size)
		{

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
				IndexData *pIndexData = pBuffer->GetIndexData();
				VertexData *pVertexData = pBuffer->GetVertexData();

				if (pIndexData)
				{
					for (uint i = 0; i < pIndexData->count; ++i)
					{
						
					}
				}

						
			}
		}

	}
}