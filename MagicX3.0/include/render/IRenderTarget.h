#ifndef _MX_RENDER_I_RENDER_TARGET_H_
#define _MX_RENDER_I_RENDER_TARGET_H_

#include "render/ITexture.h"

namespace mx
{
	namespace render
	{
		class IRenderTarget
		{
		public:
			virtual void BeginTarget() = 0;
			virtual void EndTarget() = 0;
			virtual ITexture *GetBindTexture(int index) const = 0;
			virtual ITexture *GetDepthTexture() const = 0;
			virtual ITexture *GetTexture(int index) const = 0;
		};
	}
}

#endif