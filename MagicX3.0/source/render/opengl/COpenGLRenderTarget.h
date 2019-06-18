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
			COpenGLRenderTarget(int textureCount, int width, int height, bool bHaveDepth = false);
			~COpenGLRenderTarget();
			virtual void BeginTarget();
			virtual void EndTarget();
			virtual ITexture *GetBindTexture(int index) const;
			virtual ITexture *GetDepthTexture() const;
			virtual ITexture *GetTexture(int index) const;
		private:
			std::vector<ITexture *>m_bindTexture;
			ITexture *m_depthTexture;
			int m_iWidth;
			int m_iHeight;
			GLuint m_fbo;
			int m_textureCount;
		};
	}
}

#endif