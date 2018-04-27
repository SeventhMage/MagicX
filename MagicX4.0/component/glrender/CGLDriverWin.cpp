#include "CGLDriverWin.h"

#include "glew/GL/glew.h"
#include "glew/GL/wglew.h"
	



#include <Windows.h>

namespace mx
{
	CGLDriverWin::CGLDriverWin(HDC hDC)
	{					
		// Set up pixel format descriptor with desired parameters
		PIXELFORMATDESCRIPTOR pfd = {
			sizeof(PIXELFORMATDESCRIPTOR),             // Size Of This Pixel Format Descriptor
			1,                                         // Version Number
			PFD_DRAW_TO_WINDOW |                       // Format Must Support Window
			PFD_SUPPORT_OPENGL |                       // Format Must Support OpenGL
			PFD_DOUBLEBUFFER | // Must Support Double Buffering
			PFD_STEREO,        // Must Support Stereo Buffer
			PFD_TYPE_RGBA,                             // Request An RGBA Format
			GetDeviceCaps(hDC, BITSPIXEL),                               // Select Our Color Depth
			0, 0, 0, 0, 0, 0,                          // Color Bits Ignored
			0,                                         // No Alpha Buffer
			0,                                         // Shift Bit Ignored
			0,                                         // No Accumulation Buffer
			0, 0, 0, 0,	                               // Accumulation Bits Ignored
			0,                        // Z-Buffer (Depth Buffer)
			0,        // Stencil Buffer Depth
			0,                                         // No Auxiliary Buffer
			PFD_MAIN_PLANE,                            // Main Drawing Layer
			0,                                         // Reserved
			0, 0, 0                                    // Layer Masks Ignored
		};

		int pixelFormat = ChoosePixelFormat(hDC, &pfd);
		SetPixelFormat(hDC, pixelFormat, &pfd);

		HGLRC glrc = wglCreateContext(hDC);

		if (glrc == 0) {
			exit(1);
		}

		wglMakeCurrent(hDC, glrc);

		if (glewInit() != GLEW_OK) {
			exit(1);
		}					
	}
}