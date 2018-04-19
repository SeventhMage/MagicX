#ifndef _MX_I_RENDERER_H_
#define _MX_I_RENDERER_H_

#include "RenderDef.h"

namespace mx
{
	class IDevice;
	class IRenderer
	{
	public:
		virtual void InitDriver(IDevice *pDevice) = 0;
		virtual void OnSize(int x, int y, int width, int height) = 0;
		virtual void BufferData(const void *data) = 0;
		virtual void AttributePointer(EVertexAttribute va, int offset, int stride) = 0;
		virtual void Clear() = 0;
		virtual void DrawArray(EPrimitiveType) = 0;
	};
}

#endif