#include "CCPUBuffer.h"

namespace se
{
	namespace render
	{

		CCPUBuffer::CCPUBuffer(uint id)
			:m_ID(id)			
			, m_pVertexData(nullptr)
			, m_pIndexData(nullptr)
		{

		}

		CCPUBuffer::~CCPUBuffer()
		{

		}

	}
}