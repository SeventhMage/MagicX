#ifndef _MX_RENDER_C_RENDER_PHASE_H_
#define _MX_RENDER_C_RENDER_PHASE_H_

#include "render/renderphase/IRenderPhase.h"
#include "render/renderphase/IRenderPhaseManager.h"
#include "render/IRenderTarget.h"
#include "render/IRenderQueue.h"

namespace mx
{
	namespace render
	{
		class CRenderPhase : public IRenderPhase
		{
		public:
			CRenderPhase(IRenderPhaseManager *pPhaseMgr);
			CRenderPhase(IRenderPhaseManager *pPhaseMgr, int id, int rendrTargetFlag);
			~CRenderPhase();
			virtual void Initialize(IRenderer *pRenderer, int width, int height);
			virtual void Destroy();
			virtual void Render();
			virtual int GetPhaseID() const { return 0; }

			virtual void SetEnable(bool bEnable);
			virtual bool IsEnable() const;
			virtual IRenderTarget *GetRenderTarget() const;
			virtual IRenderQueue *CreateRenderQueue(int materialId);
			virtual IRenderQueue *GetRenderQueue(int materialId);
		protected:
			bool m_bEnabled;
			IRenderTarget *m_pRenderTarget;
			IRenderPhaseManager *m_pRenderPhaseManager;
			RenderQueueGroup m_renderQueueGroup;
			int m_Id;
			int m_renderTargetFlag;
		};
	}
}

#endif