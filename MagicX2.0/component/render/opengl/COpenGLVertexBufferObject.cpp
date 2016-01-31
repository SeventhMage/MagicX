#include "glew/GL/glew.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLShaderProgram.h"
#include "OpenGLType.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{
		

		COpenGLVertexBufferObject::COpenGLVertexBufferObject(void *vertexes, int size, int first, int vertexCount, GPUBufferMode mode, GPUBufferUsage usage)
			:m_mode(mode)
			, m_vertSize(size)
			, m_first(first)
			, m_count(vertexCount)
			, m_usage(usage) 
		{
			GLDebug(glGenBuffers(1, &m_hVBO));
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
			GLDebug(glBufferData(GL_ARRAY_BUFFER, size, vertexes, GetGLGPUBufferUsage(m_usage)));
		}

		COpenGLVertexBufferObject::~COpenGLVertexBufferObject()
		{
			GLDebug(glDeleteBuffers(1, &m_hVBO));
		}

		void COpenGLVertexBufferObject::BufferData(void *vertexes, int vertSize)
		{
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
			GLDebug(glBufferData(GL_ARRAY_BUFFER, vertSize, vertexes, GetGLGPUBufferUsage(m_usage)));
		}

		void COpenGLVertexBufferObject::BufferSubData(void * data, int size, int offset)
		{
			GLDebug(glBindBuffer(GL_ARRAY_BUFFER, m_hVBO));
			GLDebug(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
		}

	}
}