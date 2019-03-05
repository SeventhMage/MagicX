#include "CShadowMapPhase.h"
#include "render/IRenderTarget.h"
#include "render/IRenderTargetManager.h"


namespace mx
{
	namespace render
	{
		CShadowMapPhase::CShadowMapPhase()
			:CRenderPhase(ERTF_DEPTH_TEXTURE)
		{
		}
		CShadowMapPhase::~CShadowMapPhase()
		{
		}
	
	}
}