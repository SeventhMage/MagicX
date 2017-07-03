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
			virtual void BufferData(const Vertices &bufferData);
			virtual Vertices *GetVertices() { return m_pVertices; };
		private:
			uint m_ID;						
			Vertices *m_pVertices;
		};
	}
}

#endif