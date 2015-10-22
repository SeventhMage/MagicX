#include "glew/GL/glew.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLShaderProgram.h"
#include "OpenGLType.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{
		

		COpenGLVertexBufferObject::COpenGLVertexBufferObject(void *vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage)
			:m_mode(mode)
			, m_vertSize(size)
			, m_first(first)
			, m_count(count)
			, m_usage(usage) 
		{
			glGenBuffers(1, &m_hVBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_hVBO);
			glBufferData(GL_ARRAY_BUFFER, size, vertexes, GetGLGPUBufferUsage(m_usage));
		}

		COpenGLVertexBufferObject::~COpenGLVertexBufferObject()
		{
			glDeleteBuffers(1, &m_hVBO);
		}

		void COpenGLVertexBufferObject::BufferData(void *vertexes, int vertSize)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_hVBO);
			glBufferData(GL_ARRAY_BUFFER, vertSize, vertexes, GetGLGPUBufferUsage(m_usage));
		}

		void COpenGLVertexBufferObject::BufferSubData(void * data, int size, int offset)
		{
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
			GLDebug(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
		}

	}
}