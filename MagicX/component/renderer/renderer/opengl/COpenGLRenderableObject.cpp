#include "COpenGLRenderableObject.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLIndexBufferObject.h"
#include "COpenGLShaderProgram.h"
#include "OpenGLType.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{
		COpenGLRenderableObject::COpenGLRenderableObject()
			:m_bEnableIndexBuffer(false)
			, m_texture(NULL)
		{
			glEnable(GL_DEPTH_TEST);
		//	glEnable(GL_CULL_FACE);
			m_shaderProgram = new COpenGLShaderProgram();
		}
		COpenGLRenderableObject::~COpenGLRenderableObject()
		{
			SAFE_DEL(m_VBO);
			SAFE_DEL(m_IBO);
			SAFE_DEL(m_shaderProgram);
		}
		void COpenGLRenderableObject::CreateVertexBufferObject(void *vertexes, int size, int first, int vertexCount, GPUBufferMode mode, GPUBufferUsage usage)
		{
			m_VBO = new COpenGLVertexBufferObject(vertexes, size, first, vertexCount, mode, usage);
		}
		void COpenGLRenderableObject::CreateIndexBufferObject(void * indices, int idxCount, RendererVariableType idxType, GPUBufferMode mode, GPUBufferUsage usage)
		{
			m_IBO = new COpenGLIndexBufferObject(indices, idxCount, idxType, mode, usage);
			m_bEnableIndexBuffer = true;
		}

		void COpenGLRenderableObject::BindTexture(int unit /* = 0 */)
		{
			if (m_texture)
			{
				GLDebug(glActiveTexture(GL_TEXTURE0 + unit));
				GLDebug(glBindTexture(GetGLTextureType(m_texture->GetTextureType()), m_texture->GetHandle()));
			}
		}

		void COpenGLRenderableObject::SetTexture(ITexture *texture, int unit /* = 0 */)
		{
			m_texture = texture;
		}

	}
}