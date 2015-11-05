#include "COpenGLTexture.h"
#include "OpenGLType.h"
#include "CTGA.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{
		COpenGLTexture::COpenGLTexture()
			:m_textureType(TT_2D)
		{			
			GLDebug(glGenTextures(1, &m_hTexture));
		}

		COpenGLTexture::~COpenGLTexture()
		{
			GLDebug(glDeleteTextures(1, &m_hTexture));
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
			m_textureType = TT_2D;
			GLDebug(glBindTexture(GL_TEXTURE_2D, m_hTexture));

			CTGA tga;
			GLbyte *pBytes = tga.ReadTGABits(filename);

			if (pBytes)
			{
				//需要提出来
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

				GLDebug(glTexImage2D(GL_TEXTURE_2D, 0, tga.GetComponents(), tga.GetWidth(), tga.GetHeight(), 0, tga.GetFormat(), GL_UNSIGNED_BYTE, pBytes));

				GLDebug(glGenerateMipmap(GL_TEXTURE_2D));
				
				return true;
			}
			return false;
		}

		bool COpenGLTexture::CreateCube(const char *front, const char *back, const char *left, const char *right, const char *top, const char *bottom)
		{
			const char *names[] = { front, back, left, right, top, bottom };
			GLenum cube[] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };

			GLDebug(glBindTexture(GL_TEXTURE_CUBE_MAP, m_hTexture));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			GLDebug(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			CTGA tga[6];
			for (int i = 0; i < 6; i++)
			{
				GLbyte *pBytes = tga[i].ReadTGABits(names[i]);
				GLDebug(glTexImage2D(cube[i], 0, tga[i].GetComponents(), tga[i].GetWidth(), tga[i].GetHeight(), 0,
					tga[i].GetFormat(), GL_UNSIGNED_BYTE, pBytes));
			}
			GLDebug(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
			m_textureType = TT_CUBE;
			return true;
		}

		bool COpenGLTexture::Create2DBit24(Byte *data, int width, int height)
		{
			m_textureType = TT_2D;
			GLDebug(glBindTexture(GL_TEXTURE_2D, m_hTexture));

			if (data)
			{
				//需要提出来
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

				GLDebug(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data));

				GLDebug(glGenerateMipmap(GL_TEXTURE_2D));

				return true;
			}
			return false;
		}

	}
}