#ifndef _MX_RENDER_C_RENDER_PHASE_H_
#define _MX_RENDER_C_RENDER_PHASE_H_

#include "render/renderphase/IRenderPhase.h"
#include "render/IRenderTarget.h"

namespace mx
{
	namespace render
	{
		class CRenderPhase : public IRenderPhase
		{
		public:
			CRenderPhase(int renderTargetFlag);
			~CRenderPhase();

			virtual void Initialize(IRenderer *pRenderer, int width, int height);
			virtual void Destroy();
			virtual void Render();
			virtual int GetPhaseID() const { return 0; }

			virtual void SetEnable(bool bEnable);
			virtual bool IsEnable() const;
		protected:
			bool m_bEnabled;
			IRenderTarget *m_pRenderTarget;
			int m_renderTargetFlag;
		};
	}
}

#endif