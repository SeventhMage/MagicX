#include "COpenGLDriver.h"
#include "GL/glew.h"
#include "GL/wglew.h"

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

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			GLenum err = glGetError();
		}

		void COpenGLDriver::OnSize(int x, int y, int width, int height)
		{
			glViewport(x, y, width, height);
		}

		void COpenGLDriver::Render()
		{
			for (auto it = m_vecRenderable.begin(); it != m_vecRenderable.end(); ++it)
			{
				if (m_vecRenderable[i])
				{
					for (uint j = 0; j < RA_NUM; ++j)
					{
						GLenum attr = GetGLRenderAttr((RenderAttribute)j);
						if (m_vecRenderableObject[i]->IsEnabled((RenderAttribute)j))
							glEnable(attr);
						else
							glDisable(attr);
					}
					//glPolygonMode(GL_FRONT_AND_BACK, GetGLPolygonMode(m_vecRenderableObject[i]->GetPolygonMode()));
					COpenGLShaderProgram *program = (COpenGLShaderProgram *)m_vecRenderableObject[i]->GetShaderProgram();
					if (program)
					{
						GLDebug(glUseProgram(program->GetHandle()));
						program->BindUniform();
					}

					m_vecRenderableObject[i]->BindTexture();



					GLDebug(glBindVertexArray(m_hVAO));
					if (m_vecRenderableObject[i]->IsEnabledIndexBuffer())
					{
						COpenGLIndexBufferObject *vio = (COpenGLIndexBufferObject *)m_vecRenderableObject[i]->GetIndexBufferObject();
						if (vio)
						{
							GLDebug(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio->GetHandle()));
							GLDebug(glDrawElements(GetGLGPUBufferMode(vio->GetGPUBufferMode()), vio->GetIndicesNum(),
								GetGLVariableType(vio->GetIndexType()), 0));
						}
					}
					else
					{
						COpenGLVertexBufferObject *vbo = (COpenGLVertexBufferObject *)m_vecRenderableObject[i]->GetVertexBufferObject();
						if (vbo)
						{
							GLDebug(glBindBuffer(GL_ARRAY_BUFFER, vbo->GetHandle()));
							GLDebug(glDrawArrays(GetGLGPUBufferMode(vbo->GetGPUBufferMode()), vbo->GetGLGPUBufferFirst(), vbo->GetVertexNum()));
						}
					}

				}
			}
			}
		}

#endif
	}
}