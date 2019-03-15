#ifndef _MX_RENDER_I_RENDER_PHASE_MANAGER_H_
#define _MX_RENDER_I_RENDER_PHASE_MANAGER_H_

#include "IRenderPhase.h"

namespace mx
{
	namespace render
	{
		class IRenderPhaseManager
		{
		public:
			virtual void LoadRenderPhase(const char *filename) = 0;
			virtual void Initialize(IRenderer *pRenderer, int width, int height) = 0;
			virtual void ProcessRenderPhase() = 0;
			virtual IRenderPhase *GetRenderPhase(int id) = 0;
		};
	}
}

#endif