#ifndef _MX_RENDER_C_RENDER_PHASE_H_
#define _MX_RENDER_C_RENDER_PHASE_H_

#include "render/renderphase/IRenderPhase.h"
#include "render/renderphase/IRenderPhaseManager.h"
#include "render/IRenderTarget.h"

namespace mx
{
	namespace render
	{
		class CRenderPhase : public IRenderPhase
		{
		public:
			CRenderPhase(IRenderPhaseManager *pPhaseMgr);
			~CRenderPhase();

			virtual void SetEnable(bool bEnable);
			virtual bool IsEnable() const;
			virtual IRenderTarget *GetRenderTarget() const;
		protected:
			bool m_bEnabled;
			IRenderTarget *m_pRenderTarget;
			IRenderPhaseManager *m_pRenderPhaseManager;
		};
	}
}

#endif