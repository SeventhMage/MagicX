#include "CCPUBuffer.h"
#include "base/seDef.h"

namespace se
{
	namespace render
	{

		CCPUBuffer::CCPUBuffer(uint id)
			:m_ID(id)								
		{
			m_pVertices = new base::Vertices;
			m_pIndices = new base::Indices;
		}

		CCPUBuffer::~CCPUBuffer()
		{
			SAFE_DEL(m_pVertices->pVertexData)
			SAFE_DEL(m_pVertices);

			SAFE_DEL(m_pIndices->pIndexData);
			SAFE_DEL(m_pIndices);
		}

		void CCPUBuffer::BufferData(const base::Vertices *bufferData)
		{
			memcpy(m_pVertices->format, bufferData->format, sizeof(m_pVertices->format));			 
			m_pVertices->count = bufferData->count;
			m_pVertices->stride = bufferData->stride;
			m_pVertices->size = bufferData->size;
			SAFE_DEL(m_pVertices->pVertexData);
			m_pVertices->pVertexData = new ubyte[m_pVertices->size];			
			memcpy(m_pVertices->pVertexData, bufferData->pVertexData, m_pVertices->size);
		}

		void CCPUBuffer::BufferData(const base::Indices *bufferData)
		{			
			m_pIndices->size = bufferData->size;
			SAFE_DEL(m_pIndices->pIndexData);
			m_pIndices->pIndexData = new ushort[m_pIndices->size];
			memcpy(m_pIndices->pIndexData, bufferData->pIndexData, m_pIndices->size);
		}

	}
}