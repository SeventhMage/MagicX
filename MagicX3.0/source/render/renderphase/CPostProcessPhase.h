#ifndef _MX_RENDER_C_POST_PROCESS_PHASE_H_
#define _MX_RENDER_C_POST_PROCESS_PHASE_H_

#include "CRenderPhase.h"

namespace mx
{
	namespace render
	{
		class CPostProcessPhase : public CRenderPhase
		{
		public:
			CPostProcessPhase(IRenderPhaseManager *pRenderPhaseMgr);
			~CPostProcessPhase();
			virtual void Initialize(IRenderer *pRenderer, int width, int height);
			virtual void Destroy();
			virtual void Render();
			virtual int GetPhaseID() const { return ERPI_POSTPROCESS; }
		};
	}
}

#endif