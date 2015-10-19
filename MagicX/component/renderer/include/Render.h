#ifndef _MX_RENDER_RENDER_H_
#define _MX_RENDER_RENDER_H_

#include <Windows.h>
#include "IRenderer.h"

namespace mx
{
	namespace render
	{		
		IRenderer *CreateRendererWin32(RendererType rendererType, HDC hDC);
		IRenderer *CreateRendererLinux(RendererType renderType, int window);
	}
}

#endif