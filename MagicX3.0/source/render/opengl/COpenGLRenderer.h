/************************************************************************/
/* ��Ⱦ��                                                               */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_RENDERER_H_
#define _MX_RENDER_C_OPENGL_RENDERER_H_

#include "../CRenderer.h"
#include "render/IRenderList.h"
#include "render/IShaderProgram.h"

namespace mx
{
	namespace render
	{
		class COpenGLRenderer : public CRenderer
		{
		public:
			COpenGLRenderer();
			virtual ~COpenGLRenderer();

			virtual void BeginRender();
			virtual void Render(IRenderable *pRenderable);
			virtual IVertexArrayObject *CreateVertexArrayObject();
			virtual void DestroyVertexArrayObject(IVertexArrayObject *pObject);
			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage);
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage);
			virtual void DestroyBufferObject(IBufferObject *object);
			virtual ITexture *CreateTexture(const char *filename);
			virtual ITexture *CreateCubeTexture(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back);
			virtual void DestroyTexture(ITexture *pTexture);
			virtual IShaderProgram *CreateShaderProgram();
			virtual void DestroyShaderProgram(IShaderProgram *pShaderProgram);
			virtual void EnableShadow(bool bEnable);
			virtual bool ShadowEnabled();
			virtual IShadowMap *GetShadowMap() { return m_pShadowMap; }
		private:
			IShadowMap *m_pShadowMap;
			bool m_bEnableShadow;
		};
	}
}

#endif