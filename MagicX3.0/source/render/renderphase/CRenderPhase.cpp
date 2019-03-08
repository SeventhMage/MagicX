#include "CRenderPhase.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		CRenderPhase::CRenderPhase(IRenderPhaseManager *pPhaseMgr)
			:m_pRenderTarget(nullptr)
			,m_pRenderPhaseManager(pPhaseMgr)
		{
		}
		CRenderPhase::~CRenderPhase()
		{
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
	}
}