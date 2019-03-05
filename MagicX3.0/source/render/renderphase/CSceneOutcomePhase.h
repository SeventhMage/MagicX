#ifndef _MX_RENDER_C_SCENE_OUTCOME_PHASE_H_
#define _MX_RENDER_C_SCENE_OUTCOME_PHASE_H_

#include "CRenderPhase.h"

namespace mx
{
	namespace render
	{
		class CSceneOutcomePhase : public CRenderPhase
		{
		public:
			CSceneOutcomePhase();
			~CSceneOutcomePhase();

			virtual int GetPhaseID() const { return ERPI_SCENEOUTCOME; }
		};
	}
}

#endif