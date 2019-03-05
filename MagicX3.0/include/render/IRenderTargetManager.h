#ifndef _MX_RENDER_TARGET_MANAGER_H_
#define _MX_RENDER_TARGET_MANAGER_H_ 

#include "IRenderTarget.h"

namespace mx
{
	namespace render
	{

		class IRenderTargetManager
		{
		public:
			virtual IRenderTarget *CreateRenderTarget(int flag, int width, int height) = 0;
		};
	}
}

#endif