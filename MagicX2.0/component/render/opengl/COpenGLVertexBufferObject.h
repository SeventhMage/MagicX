#ifndef _MX_RENDER_COPENGL_VERTEX_BUFFER_H_
#define _MX_RENDER_COPENGL_VERTEX_BUFFER_H_

#include "render/IBufferObject.h"
#include "render/ERender.h"

namespace mx
{
	namespace render
	{
		class COpenGLVertexBufferObject : public IBufferObject
		{
		public:
			COpenGLVertexBufferObject(void *vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage);
			virtual ~COpenGLVertexBufferObject();

			virtual void BufferData(void *data, int size);
			virtual void BufferSubData(void *data, int size, int offset);
			virtual GPUBufferType GetBufferType() const { return GBT_VERTEX; }
			virtual GPUBufferMode GetGPUBufferMode() const { return m_mode; }
			virtual int GetVertexNum() const { return m_count; }
			virtual uint GetHandle() const { return m_hVBO; }

			int GetGLGPUBufferFirst() { return m_first; }
		private:		
			uint m_hVBO;
			int m_vertSize;			
			int m_first;
			int m_count;
			GPUBufferMode m_mode;
			GPUBufferUsage m_usage;
		};
	}

}

#endif