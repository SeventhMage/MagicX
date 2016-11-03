#include "COpenGLVertexBufferObject.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{


		COpenGLVertexBufferObject::COpenGLVertexBufferObject(void *vertexes, int size, int first, int count, GLenum mode, GLenum usage)
			:m_mode(mode)
			, m_vertSize(size)
			, m_first(first)
			, m_count(count)
			, m_usage(usage)
		{
			GLDebug(glGenBuffers(1, &m_hVBO));
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
			GLDebug(glBufferData(GL_ARRAY_BUFFER, size, vertexes, m_usage));
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		COpenGLVertexBufferObject::~COpenGLVertexBufferObject()
		{
			GLDebug(glDeleteBuffers(1, &m_hVBO));
		}

		void COpenGLVertexBufferObject::BufferData(void *data, int size)
		{
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
			GLDebug(glBufferData(GL_ARRAY_BUFFER, size, data, m_usage));
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		void COpenGLVertexBufferObject::BufferSubData(void *data, int size, int offset)
		{
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
			GLDebug(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		void COpenGLVertexBufferObject::Bind()
		{
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
		}

	}
}