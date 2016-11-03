#include "COpenGLTexture.h"
#include "GLDebug.h"

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

		void COpenGLTexture::CreateCube(int internalformat[6], int width[6], int height[6], int format[6], int type[6], void *data[6])
		{
			GLenum cube[] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
				GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y };

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

	}
}