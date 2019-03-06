#include "CShadowMapPhase.h"
#include "render/IRenderTarget.h"
#include "render/IRenderTargetManager.h"


namespace mx
{
	namespace render
	{
		CShadowMapPhase::CShadowMapPhase(IRenderPhaseManager *pRenderPhaseMgr)
			:CRenderPhase(ERTF_DEPTH_TEXTURE, pRenderPhaseMgr)
		{
		}
		CShadowMapPhase::~CShadowMapPhase()
		{
		}
	
	}
}