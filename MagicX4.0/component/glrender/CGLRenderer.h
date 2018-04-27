#ifndef _GLRENDER_GL_RENDERER_H_
#define _GLRENDER_GL_RENDERER_H_

#include "render/IRenderer.h"
#include "device/IDevice.h"

namespace mx
{
	class CGLRenderer : public IRenderer
	{
	public:
		CGLRenderer();
		~CGLRenderer();
		
#ifdef WIN32
		virtual void InitDriver(HDC hDC);
#endif
		virtual void OnSize(int x, int y, int width, int height);
		virtual void BufferData(const void *data);
		virtual void AttributePointer(EVertexAttribute va, int offset, int stride);
		virtual void Clear();
		virtual void DrawArray(EPrimitiveType);
	};
}

#endif