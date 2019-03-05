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
		using namespace resource;
		class COpenGLTexture : public ITexture
		{
		public:
			COpenGLTexture();
			virtual ~COpenGLTexture();

			virtual void Bind(uint slot = 0);
			virtual void UnBind();
			virtual void Create2D(int internalformat, int width, int height, int format, int type, void *data);
			virtual void CreateCube(IImage *pImgRight, IImage *pImgLeft, IImage *pImgTop, IImage *pImgBottom, IImage *pImgFront, IImage *pImgBack);
			virtual void CreateDepth(int width, int height);
			virtual void Create(uint target, uint handle);
			virtual uint GetHandle() { return m_hTexture; }
		private:
			uint m_hTexture;
			GLenum m_target;	//当前纹理目标
		};
	}
}

#endif