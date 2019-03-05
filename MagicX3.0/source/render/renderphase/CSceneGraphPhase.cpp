#include "CSceneGraphPhase.h"

namespace mx
{
	namespace render
	{
		CSceneGraphPhase::CSceneGraphPhase()
			:CRenderPhase(ERTF_BIND_TEXTURE | ERTF_DEPTH_TEXTURE)
		{
		}
		CSceneGraphPhase::~CSceneGraphPhase()
		{
		}
	}
}