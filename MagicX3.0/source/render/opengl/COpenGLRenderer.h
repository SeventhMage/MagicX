/************************************************************************/
/* äÖÈ¾Æ÷                                                               */
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

			virtual void Render(IRenderable *pRenderable);
			virtual IVertexArrayObject *CreateVertexArrayObject();
			virtual void DestroyVertexArrayObject(IVertexArrayObject *pObject);
			virtual IBufferObject *CreateVertexBufferObject(void *vertexes, int size,
				int first, int count, GPUBufferMode mode, GPUBufferUsage usage);
			virtual IBufferObject *CreateIndexBufferObject(void *indices, uint idsCount,
				RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage);
			virtual void DestroyBufferObject(IBufferObject *object);
			virtual ITexture *CreateTexture(const char *filename);
			virtual ITexture *CreateCubeTexture(const char *front, const char *back, const char *left,
				const char *right, const char *top, const char *bottom);
			virtual void DestroyTexture(ITexture *pTexture);
		};
	}
}

#endif