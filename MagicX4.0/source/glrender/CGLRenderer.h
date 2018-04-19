#ifndef _GLRENDER_GL_RENDERER_H_
#define _GLRENDER_GL_RENDERER_H_

#include "render/IRenderer.h"
#include "GLDriver.h"

namespace mx
{
	class GLRenderer
	{
	public:
		GLRenderer();
		~GLRenderer();
		
		virtual void InitDriver(IDevice *pDevice);
		virtual void OnSize(int x, int y, int width, int height);
		virtual void BufferData(const void *data);
		virtual void AttributePointer(EVertexAttribute va, int offset, int stride);
		virtual void Clear();
		virtual void DrawArray(EPrimitiveType);
	};
}

#endif