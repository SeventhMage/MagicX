#ifndef _MX_RENDER_C_OPENGL_RENDERABLE_OBJECT_H_
#define _MX_RENDER_C_OPENGL_RENDERABLE_OBJECT_H_

#include "render/IRenderableObject.h"
#include "render/IBufferObject.h"
#include "render/ITexture.h"

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
			virtual void Enable(RenderAttribute attr) { m_bRenderAttrs[attr] = true; }
			virtual void Disable(RenderAttribute attr) { m_bRenderAttrs[attr] = false; }
			virtual bool IsEnabled(RenderAttribute attr) { return m_bRenderAttrs[attr]; }
			virtual void SetPolygonMode(PolygonMode pm) { m_uPolygonMode = pm; }
			virtual PolygonMode GetPolygonMode() { return m_uPolygonMode; }
			virtual void SetActive(bool bActive) { m_bActive = bActive; }
			virtual bool IsActive() { return m_bActive; }
		private:
			IBufferObject *m_VBO;
			IBufferObject *m_IBO;
			IShaderProgram *m_shaderProgram;
			ITexture *m_texture;			
			PolygonMode m_uPolygonMode;
			bool m_bRenderAttrs[RA_NUM];
			bool m_bEnableIndexBuffer;
			bool m_bActive;
		};
	}
}
#endif
