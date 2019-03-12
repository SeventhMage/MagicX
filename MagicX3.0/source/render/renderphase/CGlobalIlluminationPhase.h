#ifndef _MX_RENDER_C_GLOBAL_ILLUMINATION_PHASE_MANAGER_H_
#define _MX_RENDER_C_GLOBAL_ILLUMINATION_PHASE_MANAGER_H_

#include "CRenderPhase.h"

namespace mx
{
	namespace render
	{
		class CGlobalIlluminationPhase : public CRenderPhase
		{
		public:
			CGlobalIlluminationPhase(IRenderPhaseManager *pRenderPhaseMgr);
			~CGlobalIlluminationPhase();

			virtual void Initialize(IRenderer *pRenderer, int width, int height);
			virtual void Destroy();
			virtual void Render();
			virtual int GetPhaseID() const { return ERPI_GLOBALILLUMINATION; }
		};
	}
}

#endif