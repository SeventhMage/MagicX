#ifndef _C_OPENGL_TEXTURE_H_
#define _C_OPENGL_TEXTURE_H_

#include "../../include/ITexture.h"
#include "glew/GL/glew.h"

namespace mx
{
	namespace render
	{
		class COpenGLTexture : public ITexture
		{
		public:
			COpenGLTexture();
			virtual ~COpenGLTexture();

			virtual bool Create(const char *filename, TextureType texType);
			virtual TextureType GetTextureType() { return m_textureType; }
			virtual uint GetHandle() { return m_hTexture; }
		private:
			bool Create2D(const char *filename);
		private:
			GLuint m_hTexture;
			TextureType m_textureType;
		};
	}
}

#endif // !_COPENGL_TEXTURE_H_INC_
