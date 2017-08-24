#ifndef _RENDER_S_RENDER_MEMORY_H_
#define _RENDER_S_RENDER_MEMORY_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		typedef struct SRenderMemory
		{
			uint width;
			uint height;
			char *addr;
		}RenderMemory;
	}
}

#endif