#include "COpenGLIndexBufferObject.h"
#include "GLDebug.h"
#include "OpenGLType.h"


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
			GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetGLVariableSize(idsType) * idsCount, indices, usage));
		}

		COpenGLIndexBufferObject::~COpenGLIndexBufferObject()
		{
			GLDebug(glDeleteBuffers(1, &m_IBO));
		}

		void COpenGLIndexBufferObject::BufferData(void *indices, int idsSize)
		{
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
			GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, idsSize, indices, m_gpuBufferUsage));
		}

		void COpenGLIndexBufferObject::BufferSubData(void *data, int size, int offset)
		{
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
			GLDebug(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
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