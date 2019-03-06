#include "CRenderPhase.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		CRenderPhase::CRenderPhase(int renderTargetFlag, IRenderPhaseManager *pPhaseMgr)
			:m_pRenderTarget(nullptr)
			,m_renderTargetFlag(renderTargetFlag)
			,m_pRenderPhaseManager(pPhaseMgr)
		{
		}
		CRenderPhase::~CRenderPhase()
		{
		}
		void CRenderPhase::Initialize(IRenderer *pRenderer, int width, int height)
		{
			m_pRenderTarget = pRenderer->GetRenderTargetManager()->CreateRenderTarget(m_renderTargetFlag, width, height);
		}
		void CRenderPhase::Destroy()
		{
			SAFE_DEL(m_pRenderTarget);
		}
		void CRenderPhase::SetEnable(bool bEnable)
		{
			m_bEnabled = bEnable;
		}
		bool CRenderPhase::IsEnable() const
		{
			return m_bEnabled;
		}
		IRenderTarget * CRenderPhase::GetRenderTarget() const
		{
			return m_pRenderTarget;
		}
		void CRenderPhase::Render()
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