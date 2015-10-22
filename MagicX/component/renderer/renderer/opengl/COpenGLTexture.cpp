#include "COpenGLTexture.h"
#include "OpenGLType.h"
#include "CTGA.h"

namespace mx
{
	namespace render
	{
		COpenGLTexture::COpenGLTexture()
		{			
			glGenTextures(1, &m_hTexture);
		}

		COpenGLTexture::~COpenGLTexture()
		{
			glDeleteTextures(1, &m_hTexture);
		}

		bool COpenGLTexture::Create(const char *filename, TextureType texType)
		{			
			//glActiveTexture(GL_TEXTURE0);
			switch (texType)
			{
			case TT_1D:
				break;
			case TT_2D:
				return Create2D(filename);
				break;
			case TT_3D:
				break;
			case TT_CUBE:
				break;
			}
			
			return false;
		}

		bool COpenGLTexture::Create2D(const char *filename)
		{
			glBindTexture(GL_TEXTURE_2D, m_hTexture);

			CTGA tga;
			GLbyte *pBytes = tga.ReadTGABits(filename);

			if (pBytes)
			{
				//需要提出来
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				glTexImage2D(GL_TEXTURE_2D, 0, tga.GetComponents(), tga.GetWidth(), tga.GetHeight(), 0, tga.GetFormat(), GL_UNSIGNED_BYTE, pBytes);

				glGenerateMipmap(GL_TEXTURE_2D);
				
				return true;
			}
			return false;
		}

	}
}