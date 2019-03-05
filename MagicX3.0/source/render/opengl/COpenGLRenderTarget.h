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
			COpenGLTexture *m_bindTexture;
			COpenGLTexture *m_depthTexture;
			int m_iWidth;
			int m_iHeight;
			GLuint m_fbo;
		};
	}
}

#endif