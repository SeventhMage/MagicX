#include "CSceneGraphPhase.h"

namespace mx
{
	namespace render
	{
		CSceneGraphPhase::CSceneGraphPhase(IRenderPhaseManager *pRenderPhaseMgr)
			:CRenderPhase(ERTF_BIND_TEXTURE | ERTF_DEPTH_TEXTURE, pRenderPhaseMgr)
		{
		}
		CSceneGraphPhase::~CSceneGraphPhase()
		{
		}
	}
}