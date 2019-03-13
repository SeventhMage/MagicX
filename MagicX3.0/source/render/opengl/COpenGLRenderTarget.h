#ifndef _MX_RENDER_C_OPENGL_RENDER_TARGET_H_
#define _MX_RENDER_C_OPENGL_RENDER_TARGET_H_

#include "render/IRenderTarget.h"
#include "COpenGLTexture.h"


namespace mx
{
	namespace render
	{
		class COpenGLRenderTarget : public IRenderTarget
		{
		public:
			COpenGLRenderTarget(int renderTargetFlag, int width, int height);
			~COpenGLRenderTarget();
			virtual void BeginTarget();
			virtual void EndTarget();
			virtual ITexture *GetBindTexture() const;
			virtual ITexture *GetDepthTexture() const;
		private:
			enum ETextureFlag
			{
				ETF_COLOR = 0,
				ETF_POSITION,
				ETF_NORMAL,
				ETF_DEPTH,

				ETF_NUM,
			};
			COpenGLTexture *m_Texture[ETF_NUM];
			int m_iWidth;
			int m_iHeight;
			GLuint m_fbo;
		};
	}
}

#endif