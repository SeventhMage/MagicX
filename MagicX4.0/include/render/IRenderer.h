#ifndef _MX_I_RENDERER_H_
#define _MX_I_RENDERER_H_

#include "RenderDef.h"

namespace mx
{
	class IRenderer
	{
	public:
		virtual void BufferData(const void *data) = 0;
		virtual void AttributePointer(EVertexAttribute va, int offset, int stride) = 0;
		virtual void Clear();
		virtual void DrawArray(EPrimitiveType) = 0;
	};
}

#endif