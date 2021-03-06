#ifndef _MX_RENDER_C_OPENGL_RENDERABLE_OBJECT_H_
#define _MX_RENDER_C_OPENGL_RENDERABLE_OBJECT_H_

#include "../../include/IRenderableObject.h"
#include "../../include/IBufferObject.h"
#include "../../Include/ITexture.h"
#include "../../include/IShaderProgram.h"

namespace mx
{
	namespace render
	{
		class COpenGLRenderableObject : public IRenderableObject
		{
		public:
			COpenGLRenderableObject();
			virtual ~COpenGLRenderableObject();

			virtual void CreateVertexBufferObject(void *vertexes, int size, int first, int vertexCount, GPUBufferMode mode, GPUBufferUsage usage);
			virtual void CreateIndexBufferObject(void *indices, uint idsCount, RendererVariableType idsType, uint vertCount, GPUBufferMode mode, GPUBufferUsage usage);
			virtual IShaderProgram *GetShaderProgram() { return m_shaderProgram; }
			virtual IBufferObject *GetVertexBufferObject() { return m_VBO; }
			virtual IBufferObject *GetIndexBufferObject() { return m_IBO; }
			virtual void EnableIndexBuffer(bool enable) { m_bEnableIndexBuffer = enable; }
			virtual bool IsEnabledIndexBuffer() { return m_bEnableIndexBuffer; }
			virtual void BindTexture(int unit = 0);
			virtual void SetTexture(ITexture *texture, int unit = 0);
		private:
			IBufferObject *m_VBO;
			IBufferObject *m_IBO;
			IShaderProgram *m_shaderProgram;
			ITexture *m_texture;
			bool m_bEnableIndexBuffer;
		};
	}
}
#endif
