/************************************************************************/
/* 纹理                                                                 */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_TEXTURE_H_
#define _MX_RENDER_C_OPENGL_TEXTURE_H_

#include "render/ITexture.h"
#include "GL/glew.h"

namespace mx
{
	namespace render
	{
		class COpenGLTexture : public ITexture
		{
		public:
			COpenGLTexture();
			virtual ~COpenGLTexture();

			virtual void Bind(uint slot = 0);
			virtual void UnBind();
			virtual void Create2D(int internalformat, int width, int height, int format, int type, void *data);
			virtual void CreateCube(int internalformat[6], int width[6], int height[6], int format[6], int type[6], void *data[6]);
			virtual uint GetHandle() { return m_hTexture; }
		private:
			uint m_hTexture;
			GLenum m_target;	//当前纹理目标
		};
	}
}

#endif