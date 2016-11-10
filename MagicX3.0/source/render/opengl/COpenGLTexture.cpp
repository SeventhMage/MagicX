#include "COpenGLTexture.h"
#include "GLDebug.h"
#include "OpenGLType.h"

namespace mx
{
	namespace render
	{


		COpenGLTexture::COpenGLTexture()
		{
			GLDebug(glGenTextures(1, &m_hTexture));
		}

		COpenGLTexture::~COpenGLTexture()
		{
			GLDebug(glDeleteTextures(1, &m_hTexture));
		}

		void COpenGLTexture::Create2D(int internalformat, int width, int height, int format, int type, void *data)
		{
			m_target = GL_TEXTURE_2D;
			GLDebug(glBindTexture(GL_TEXTURE_2D, m_hTexture));

			if (data)
			{
				//需要提出来
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

				GLDebug(glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, type, data));

				GLDebug(glGenerateMipmap(GL_TEXTURE_2D));

				GLDebug(glBindTexture(GL_TEXTURE_2D, 0));
			}
		}

		void COpenGLTexture::CreateCube(IImage *pImgFront, IImage *pImgBack, IImage *pImgLeft, 
			IImage *pImgRight, IImage *pImgTop, IImage *pImgBottom)
		{
			GLenum cube[] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };

			int internalformat[6] = { GetGLColorFormat(pImgFront->GetComponents()), GetGLColorFormat(pImgBack->GetComponents()), GetGLColorFormat(pImgLeft->GetComponents()), GetGLColorFormat(pImgRight->GetComponents()), GetGLColorFormat(pImgTop->GetComponents()), GetGLColorFormat(pImgBottom->GetComponents()) };
			int width[6] = { pImgFront->GetWidth(), pImgBack->GetWidth(), pImgLeft->GetWidth(), pImgRight->GetWidth(), pImgTop->GetWidth(), pImgBottom->GetWidth() };
			int height[6] = { pImgFront->GetHeight(), pImgBack->GetHeight(), pImgLeft->GetHeight(), pImgRight->GetHeight(), pImgTop->GetHeight(), pImgBottom->GetHeight() };
			int format[6] = { GetGLColorFormat(pImgFront->GetFormat()), GetGLColorFormat(pImgBack->GetFormat()), GetGLColorFormat(pImgLeft->GetFormat()), GetGLColorFormat(pImgRight->GetFormat()), GetGLColorFormat(pImgTop->GetFormat()), GetGLColorFormat(pImgBottom->GetFormat()) };
			int type[6] = { GetGLPixelType(pImgFront->GetPixelType()), GetGLPixelType(pImgBack->GetPixelType()), GetGLPixelType(pImgLeft->GetPixelType()), GetGLPixelType(pImgRight->GetPixelType()), GetGLPixelType(pImgTop->GetPixelType()), GetGLPixelType(pImgBottom->GetPixelType()) };
			void *data[6] = { pImgFront->GetData(), pImgBack->GetData(), pImgLeft->GetData(), pImgRight->GetData(), pImgTop->GetData(), pImgBottom->GetData() };

			m_target = GL_TEXTURE_CUBE_MAP;

			GLDebug(glBindTexture(GL_TEXTURE_CUBE_MAP, m_hTexture));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			for (int i = 0; i < 6; i++)
			{
				GLDebug(glTexImage2D(cube[i], 0, internalformat[i], width[i], height[i], 0,
					format[i], type[i], data[i]));
			}
			GLDebug(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
		}

		void COpenGLTexture::Bind(uint slot)
		{
			GLDebug(glActiveTexture(GL_TEXTURE0 + slot));
			GLDebug(glBindTexture(m_target, m_hTexture));
		}

		void COpenGLTexture::UnBind()
		{			
			GLDebug(glBindTexture(m_target, 0));
		}

	}
}