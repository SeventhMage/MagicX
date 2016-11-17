#include "COpenGLDriver.h"
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{


		COpenGLDriver::COpenGLDriver()
		{
			
		}

		COpenGLDriver::~COpenGLDriver()
		{

		}

#ifdef WIN32
		void COpenGLDriver::InitDriverWin32(HDC hDC)
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
			  
			GLDebug(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLDebug(glEnable(GL_DEPTH_TEST));
			GLDebug(glEnable(GL_CULL_FACE));
		}
#endif

		void COpenGLDriver::OnSize(int x, int y, int width, int height)
		{
			GLDebug(glViewport(x, y, width, height));
		}
	}
}