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

		void COpenGLTexture::CreateCube(IImage *pImgRight, IImage *pImgLeft, IImage *pImgTop, 
			IImage *pImgBottom, IImage *pImgFront, IImage *pImgBack)
		{			
			IImage *pImage[6] = {pImgRight, pImgLeft, pImgTop, pImgBottom, pImgFront, pImgBack};

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
				GLDebug(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GetGLColorFormat(pImage[i]->GetComponents()), pImage[i]->GetWidth(), pImage[i]->GetHeight(), 0,
					GetGLColorFormat(pImage[i]->GetFormat()), GetGLPixelType(pImage[i]->GetPixelType()), (void *)pImage[i]->GetData()));
			}
			GLDebug(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));
		}

		void COpenGLTexture::CreateDepth(int width, int height)
		{
			m_target = GL_TEXTURE_2D;
			GLDebug(glBindTexture(GL_TEXTURE_2D, m_hTexture));
			GLDebug(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
			GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
			GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
			GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
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

		void COpenGLTexture::Create(uint target, uint handle)
		{
			m_target = target;
			m_hTexture = handle;
		}

	}
}