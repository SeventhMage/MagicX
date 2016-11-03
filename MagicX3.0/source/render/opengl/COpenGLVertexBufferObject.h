/************************************************************************/
/* 顶点缓冲区对象                                                       */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_VERTEX_BUFFER_OBJECT_H_
#define _MX_RENDER_C_OPENGL_VERTEX_BUFFER_OBJECT_H_

#include "render/IBufferObject.h"
#include "render/ERender.h"
#include "mxType.h"
#include "GL/glew.h"

namespace mx
{
	namespace render
	{
		class COpenGLVertexBufferObject : public IBufferObject
		{
		public:
			COpenGLVertexBufferObject(void *vertexes, int size, int first, int count, GLenum mode, GLenum usage);
			virtual ~COpenGLVertexBufferObject();
			
			virtual void Bind();

			virtual void BufferData(void *data, int size);
			virtual void BufferSubData(void *data, int size, int offset);
			virtual GPUBufferType GetBufferType() const { return GBT_VERTEX; }
			virtual GLenum GetGPUBufferMode() const { return m_mode; }
			virtual int GetVertexNum() const { return m_count; }
			virtual uint GetHandle() const { return m_hVBO; }

			int GetGLGPUBufferFirst() { return m_first; }
		private:
			uint m_hVBO;
			int m_vertSize;
			int m_first;
			int m_count;
			GLenum m_mode;
			GLenum m_usage;
		};
	}
}

#endif