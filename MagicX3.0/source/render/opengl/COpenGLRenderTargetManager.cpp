#include "COpenGLRenderTargetManager.h"
#include "COpenGLRenderTarget.h"

namespace mx
{
	namespace render
	{
		IRenderTarget * COpenGLRenderTargetManager::CreateRenderTarget(int textureCount, int width, int height, bool bHaveDepth)
		{
			return new COpenGLRenderTarget(textureCount, width, height, bHaveDepth);
		}
	}
}