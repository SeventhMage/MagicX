#include "COpenGLIndexBufferObject.h"
#include "GLDebug.h"
#include "OpenGLType.h"

namespace mx
{
	namespace render
	{

		COpenGLIndexBufferObject::COpenGLIndexBufferObject(void *indices, uint idsCount, RendererVariableType idsType, uint vertCount, GPUBufferMode mode, GPUBufferUsage usage)
			:m_gpuBufferMode(mode)
			, m_gpuBufferUsage(usage)
			, m_uVerticesNum(vertCount)
			, m_uIndicesNum(idsCount)
		{
			GLDebug(glGenBuffers(1, &m_IBO));
			GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO));
			GLDebug(glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetGLVariableSize(idsType) * idsCount, indices, GetGLGPUBufferUsage(usage)));
		}

		COpenGLIndexBufferObject::~COpenGLIndexBufferObject()
		{
			GLDebug(glDeleteBuffers(1, &m_IBO));
		}

		void COpenGLIndexBufferObject::BufferData(void * indices, int idxSize)
		{
		}


		
	}
}