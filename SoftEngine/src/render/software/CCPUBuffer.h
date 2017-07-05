#ifndef _RENDER_C_CPU_BUFFER_H_
#define _RENDER_C_CPU_BUFFER_H_

#include "render/IBuffer.h"
#include "base/VertexAttribute.h"

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
			virtual void BufferData(const base::Vertices *bufferData);
			virtual void BufferData(const base::Indices *bufferData);
			virtual base::Vertices *GetVertices() { return m_pVertices; };
			virtual base::Indices *GetIndices() { return m_pIndices; }
		private:
			uint m_ID;						
			base::Vertices *m_pVertices;
			base::Indices *m_pIndices;
		};
	}
}

#endif