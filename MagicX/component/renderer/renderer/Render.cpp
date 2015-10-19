#include "../include/Render.h"
#include "../include/IRenderDriver.h"
#include "opengl/COpenGLRenderer.h"

namespace mx
{
	namespace render
	{
		IRenderer *CreateRendererWin32(RendererType rendererType, HDC hDC)
		{
			IRenderer *renderer = NULL;
			switch (rendererType)
			{
			case RT_OPENGL:
				renderer = new COpenGLRenderer();
				break;
			case RT_DX9:
				break;
			case RT_DX11:
				break;
			default:
				;
			}
			
			return renderer;
		}

		IRenderer *CreateRendererLinux(RendererType rendererType, int window)
		{
			IRenderer *renderer = NULL;
			switch (rendererType)
			{
			case RT_OPENGL:
				break;
			case RT_DX9:
				break;
			case RT_DX11:
				break;
			default:
				;
			}
			return renderer;
		}
	}
}