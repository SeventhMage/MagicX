#ifndef _MX_RENDER_I_RENDER_TARGET_H_
#define _MX_RENDER_I_RENDER_TARGET_H_

#include "render/ITexture.h"

namespace mx
{
	namespace render
	{
		enum ERenderTargetFlag
		{
			ERTF_DEFAULT = 0,
			ERTF_COLOR_TEXTURE = 1 << 0,
			ERTF_POSITION_TEXTURE = 1 << 1,
			ERTF_NORMAL_TEXTURE = 1 << 2,
			ERTF_DEPTH_TEXTURE = 1 << 3,
		};

		class IRenderTarget
		{
		public:
			virtual void BeginTarget() = 0;
			virtual void EndTarget() = 0;
			virtual ITexture *GetBindTexture() const = 0;
			virtual ITexture *GetDepthTexture() const = 0;
			virtual ITexture *GetTexture(int flag) const = 0;
		};
	}
}

#endif