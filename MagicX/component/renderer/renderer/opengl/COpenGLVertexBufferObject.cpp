#include "glew/GL/glew.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLShaderProgram.h"
#include "OpenGLType.h"

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
			glBindBuffer(GL_VERTEX_ARRAY, m_hVBO);
			glBufferData(GL_VERTEX_ARRAY, size, vertexes, GetGLGPUBufferUsage(m_usage));
		}

		COpenGLVertexBufferObject::~COpenGLVertexBufferObject()
		{
			glDeleteBuffers(1, &m_hVBO);
		}

		void COpenGLVertexBufferObject::BufferData(void *vertexes, int vertSize)
		{
			glBindBuffer(GL_VERTEX_ARRAY, m_hVBO);
			glBufferData(GL_VERTEX_ARRAY, vertSize, vertexes, GetGLGPUBufferUsage(m_usage));
		}

		void COpenGLVertexBufferObject::BufferSubData(void * data, int size, int offset)
		{
			glBindBuffer(GL_VERTEX_ARRAY, m_hVBO);
			glBufferSubData(GL_VERTEX_ARRAY, offset, size, data);
		}

	}
}