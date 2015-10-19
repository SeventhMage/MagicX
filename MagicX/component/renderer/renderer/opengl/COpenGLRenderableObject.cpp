#include "COpenGLRenderableObject.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLIndexBufferObject.h"
#include "COpenGLShaderProgram.h"

namespace mx
{
	namespace render
	{
		COpenGLRenderableObject::COpenGLRenderableObject()
			:m_bEnableIndexBuffer(false)
		{
			m_shaderProgram = new COpenGLShaderProgram();
		}
		COpenGLRenderableObject::~COpenGLRenderableObject()
		{
			SAFE_DEL(m_VBO);
			SAFE_DEL(m_IBO);
			SAFE_DEL(m_shaderProgram);
		}
		void COpenGLRenderableObject::CreateVertexBufferObject(void *vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage)
		{
			m_VBO = new COpenGLVertexBufferObject(vertexes, size, first, count, mode, usage);
		}
		void COpenGLRenderableObject::CreateIndexBufferObject(void * indices, int idxCount, RendererVariableType idxType, GPUBufferMode mode, GPUBufferUsage usage)
		{
			m_IBO = new COpenGLIndexBufferObject(indices, idxCount, idxType, mode, usage);
			m_bEnableIndexBuffer = true;
		}
	}
}