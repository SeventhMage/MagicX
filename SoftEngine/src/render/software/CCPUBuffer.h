#ifndef _RENDER_C_CPU_BUFFER_H_
#define _RENDER_C_CPU_BUFFER_H_

#include "render/IBuffer.h"
#include "render/VertexAttribute.h"

namespace se
{
	namespace render
	{
		class CCPUBuffer : public IBuffer
		{
		public:
			CCPUBuffer(uint id);
			virtual ~CCPUBuffer();
			virtual uint GetID()const{ return m_ID; }
			virtual EBufferType GetBufferType()const { return BT_CPU; }
			virtual void BufferData(const SIndexData &bufferData);
			virtual IndexData *GetIndexData();
			virtual VertexData *GetVertexData();
		private:
			uint m_ID;			
			IndexData *m_pIndexData;
			VertexData *m_pVertexData;
		};
	}
}

#endif