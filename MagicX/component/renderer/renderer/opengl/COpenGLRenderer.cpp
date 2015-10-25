#include "COpenGLRenderer.h"
#include "glew/gl/glew.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLIndexBufferObject.h"
#include "COpenGLGPUBuffer.h"
#include "COpenGLTexture.h"

namespace mx
{
	namespace render
	{


		COpenGLRenderer::COpenGLRenderer()
		{
		}

		COpenGLRenderer::~COpenGLRenderer()
		{
			for (uint i = 0; i < m_vecBuffer.size(); ++i)
			{
				SAFE_DEL(m_vecBuffer[i]);
			}
		}

		bool COpenGLRenderer::InitRendererWin32(HDC hDC)
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

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			GLenum err = glGetError();
			return true;
		}

		void COpenGLRenderer::SetViewport(int left, int top, int width, int height)
		{
			glViewport(left, top, width, height);
		}

		void COpenGLRenderer::Render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (uint i = 0; i < m_vecBuffer.size(); ++i)
			{
				if (m_vecBuffer[i])
				{
					m_vecBuffer[i]->Render();
				}
			}
		}

		IGPUBuffer * COpenGLRenderer::CreateGPUBuffer(int stride)
		{
			IGPUBuffer *buffer = new COpenGLGPUBuffer(stride);
			m_vecBuffer.push_back(buffer);
			return buffer;
		}

		void COpenGLRenderer::DestroyGPUBuffer(IGPUBuffer *gpuBuffer)
		{
			for (uint i = 0; i < m_vecBuffer.size(); ++i)
			{
				if (m_vecBuffer[i] == gpuBuffer)
				{
					m_vecBuffer.erase(i + m_vecBuffer.begin());
					SAFE_DEL(gpuBuffer);
				}
			}
		}

		ITexture * COpenGLRenderer::CreateTexture(const char * filename, TextureType texType)
		{
			ITexture *tex = new COpenGLTexture();
			tex->Create(filename, texType);
			return tex;
		}

		ITexture * COpenGLRenderer::CreateCubeTexture(const char * front, const char * back, const char * left, const char * right, const char * top, const char * bottom)
		{
			ITexture *tex = new COpenGLTexture();
			tex->CreateCube(front, back, left, right, top, bottom);
			return tex;
		}

		void COpenGLRenderer::ClearColor(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
		}

		void COpenGLRenderer::Clear(uint mask)
		{
			glClear(mask);
		}

		void COpenGLRenderer::Enable(uint cap)
		{
			glEnable(cap);
		}

		void COpenGLRenderer::Disable(uint cap)
		{
			glDisable(cap);
		}

	}
}