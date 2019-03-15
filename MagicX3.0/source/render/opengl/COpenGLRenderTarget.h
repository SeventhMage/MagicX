#ifndef _MX_RENDER_C_OPENGL_RENDER_TARGET_H_
#define _MX_RENDER_C_OPENGL_RENDER_TARGET_H_

#include "render/IRenderTarget.h"
#include "COpenGLTexture.h"

#include <map>

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
			virtual ITexture *GetTexture(int flag) const;
		private:

			
			std::map<int, ITexture *>m_Texture;
			int m_iWidth;
			int m_iHeight;
			GLuint m_fbo;
		};
	}
}

#endif