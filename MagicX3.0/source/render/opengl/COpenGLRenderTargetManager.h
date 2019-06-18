#ifndef _MX_RENDER_COPENGL_RENDER_TARGET_MANAGER_H_
#define _MX_RENDER_COPENGL_RENDER_TARGET_MANAGER_H_

#include "render/IRenderTargetManager.h"

namespace mx
{
	namespace render
	{
		class COpenGLRenderTargetManager : public IRenderTargetManager
		{
		public:
			virtual IRenderTarget *CreateRenderTarget(int textureCount, int width, int height, bool bHaveDepth);
		};
	}
}

#endif