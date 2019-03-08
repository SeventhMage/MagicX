#include "CSceneGraphPhase.h"
#include "mxDef.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		CSceneGraphPhase::CSceneGraphPhase(IRenderPhaseManager *pRenderPhaseMgr)
			:CRenderPhase(pRenderPhaseMgr)
		{
		}
		CSceneGraphPhase::~CSceneGraphPhase()
		{
		}

		void CSceneGraphPhase::Initialize(IRenderer *pRenderer, int width, int height)
		{
			m_pRenderTarget = pRenderer->GetRenderTargetManager()->CreateRenderTarget(ERTF_BIND_TEXTURE | ERTF_DEPTH_TEXTURE, width, height);
		}

		void CSceneGraphPhase::Destroy()
		{
			SAFE_DEL(m_pRenderTarget);
		}

		void CSceneGraphPhase::Render()
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