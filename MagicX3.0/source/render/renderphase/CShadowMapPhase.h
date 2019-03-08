#ifndef _MX_RENDER_C_SHADOW_MAP_PHASE_H_
#define _MX_RENDER_C_SHADOW_MAP_PHASE_H_

#include "CRenderPhase.h"

namespace mx
{
	namespace render
	{
		class CShadowMapPhase : public CRenderPhase
		{
		public:
			CShadowMapPhase(IRenderPhaseManager *pRenderPhaseMgr);
			~CShadowMapPhase();
			virtual void Initialize(IRenderer *pRenderer, int width, int height);
			virtual void Destroy();
			virtual void Render();
			virtual int GetPhaseID() const { return ERPI_SHADOWMAP; }
		};
	}
}

#endif