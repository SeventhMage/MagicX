#include "CPostProcessPhase.h"

namespace mx
{
	namespace render
	{
		CPostProcessPhase::CPostProcessPhase(IRenderPhaseManager *pRenderPhaseMgr)
			:CRenderPhase(ERTF_BIND_TEXTURE, pRenderPhaseMgr)
		{
		}
		CPostProcessPhase::~CPostProcessPhase()
		{
		}
	}
}