#include "COpenGLIndexBufferObject.h"
#include "GLDebug.h"


namespace mx
{
	namespace render
	{


		COpenGLIndexBufferObject::COpenGLIndexBufferObject(void *indices, GLsizei idsCount, GLenum idsType, GLenum mode, GLenum usage)
			:m_gpuBufferMode(mode)
			, m_gpuBufferUsage(usage)
			, m_uIndicesNum(idsCount)
			, m_idsType(idsType)
		{
			GLDebug(glGenBuffers(1, &m_IBO));
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
			GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, idsType * idsCount, indices, usage));
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

		COpenGLIndexBufferObject::~COpenGLIndexBufferObject()
		{
			GLDebug(glDeleteBuffers(1, &m_IBO));
		}

		void COpenGLIndexBufferObject::BufferData(void *indices, int idsSize)
		{
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
			GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, idsSize, indices, m_gpuBufferUsage));
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

		void COpenGLIndexBufferObject::BufferSubData(void *data, int size, int offset)
		{
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
			GLDebug(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

		void COpenGLIndexBufferObject::Bind()
		{
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
		}

		void COpenGLIndexBufferObject::UnBind()
		{
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

	}
}