#ifndef _MX_RENDER_C_RENDER_PHASE_MANAGER_H_
#define _MX_RENDER_C_RENDER_PHASE_MANAGER_H_

#include "render/renderphase/IRenderPhaseManager.h"

#include <vector>

namespace mx
{
	namespace render
	{
		class CRenderPhaseManager : public IRenderPhaseManager
		{
		public:
			CRenderPhaseManager();
			~CRenderPhaseManager();

			void LoadRenderPhase(const char *filename);
			void Initialize(IRenderer *pRenderer, int width, int height);
			void ProcessRenderPhase();
			IRenderPhase *GetRenderPhase(int id);

		private:
			IRenderPhase *CreateRenderPhase(int id, const char *filename);
		private:
			std::vector<IRenderPhase *> m_vecRenderPhase;
		};
	}
}

#endif