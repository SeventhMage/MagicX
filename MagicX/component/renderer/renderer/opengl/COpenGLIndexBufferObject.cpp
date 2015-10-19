#include "COpenGLIndexBufferObject.h"

namespace mx
{
	namespace render
	{

		COpenGLIndexBufferObject::COpenGLIndexBufferObject(void *indices, int idxCount, RendererVariableType idxType, GPUBufferMode mode, GPUBufferUsage usage)
			:m_gpuBufferMode(mode)
			, m_gpuBufferUsage(usage)
		{
		}

		COpenGLIndexBufferObject::~COpenGLIndexBufferObject()
		{

		}

		void COpenGLIndexBufferObject::BufferData(void * indices, int idxSize)
		{
		}


		
	}
}