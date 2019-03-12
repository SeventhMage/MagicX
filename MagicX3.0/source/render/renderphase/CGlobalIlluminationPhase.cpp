#include "CGlobalIlluminationPhase.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CGlobalIlluminationPhase::CGlobalIlluminationPhase(IRenderPhaseManager *pRenderPhaseMgr)
			:CRenderPhase(pRenderPhaseMgr)
		{

		}

		CGlobalIlluminationPhase::~CGlobalIlluminationPhase()
		{
		}

		void CGlobalIlluminationPhase::Initialize(IRenderer * pRenderer, int width, int height)
		{
			m_pRenderTarget = pRenderer->GetRenderTargetManager()->CreateRenderTarget(ERTF_DEPTH_TEXTURE, 32, 32);
		}

		void CGlobalIlluminationPhase::Destroy()
		{
			SAFE_DEL(m_pRenderTarget);
		}

		void CGlobalIlluminationPhase::Render()
		{
			if (!IsEnable()) return;
			if (m_pRenderTarget)
			{
				m_pRenderTarget->BeginTarget();
				RENDERER->Render();
				m_pRenderTarget->EndTarget();
			}
		}
	}
}