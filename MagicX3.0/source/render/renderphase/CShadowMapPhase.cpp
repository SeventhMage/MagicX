#include "CShadowMapPhase.h"
#include "render/IRenderTarget.h"
#include "render/IRenderTargetManager.h"
#include "mxDef.h"
#include "mx.h"


namespace mx
{
	namespace render
	{
		CShadowMapPhase::CShadowMapPhase(IRenderPhaseManager *pRenderPhaseMgr)
			:CRenderPhase(pRenderPhaseMgr)
		{
		}
		CShadowMapPhase::~CShadowMapPhase()
		{
		}

		void CShadowMapPhase::Initialize(IRenderer *pRenderer, int width, int height)
		{
			m_pRenderTarget = pRenderer->GetRenderTargetManager()->CreateRenderTarget(ERTF_DEPTH_TEXTURE, width, height);
		}

		void CShadowMapPhase::Destroy()
		{
			SAFE_DEL(m_pRenderTarget);
		}

		void CShadowMapPhase::Render()
		{
			if (!IsEnable()) return;
			if (m_pRenderTarget)
			{
				m_pRenderTarget->BeginTarget();
				RENDERER->SetRenderShadowMap(true);
				RENDERER->Render();
				RENDERER->SetRenderShadowMap(false);
				m_pRenderTarget->EndTarget();
			}
		}


	}
}