#include "COpenGLRenderTargetManager.h"
#include "COpenGLRenderTarget.h"

namespace mx
{
	namespace render
	{
		IRenderTarget * COpenGLRenderTargetManager::CreateRenderTarget(int flag, int width, int height)
		{
			return new COpenGLRenderTarget(flag, width, height);
		}
	}
}