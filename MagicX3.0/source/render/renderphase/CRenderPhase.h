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
			CRenderPhase(IRenderPhaseManager *pPhaseMgr, int id, int rendrTargetFlag, int width, int height);
			~CRenderPhase();
			virtual void Initialize(IRenderer *pRenderer, int width, int height);
			virtual void Destroy();
			virtual void Render();
			virtual int GetPhaseID() const { return m_Id; }

			virtual void SetEnable(bool bEnable);
			virtual bool IsEnable() const;
			virtual IRenderTarget *GetRenderTarget() const;
			virtual IRenderQueue *CreateRenderQueue(int materialId);
			virtual IRenderQueue *GetRenderQueue(int materialId);
			virtual void SetCameraType(const char *camType) { m_cameraType = camType; }
		protected:
			bool m_bEnabled;
			IRenderTarget *m_pRenderTarget;
			IRenderPhaseManager *m_pRenderPhaseManager;
			RenderQueueGroup m_renderQueueGroup;
			int m_Id;
			int m_renderTargetFlag;
			int m_iWidth;
			int m_iHeight;
			std::string m_cameraType;
		};
	}
}

#endif