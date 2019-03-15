#include "CRenderPhase.h"
#include "mx.h"
#include "../CRenderQueue.h"

namespace mx
{
	namespace render
	{
		CRenderPhase::CRenderPhase(IRenderPhaseManager *pPhaseMgr)
			:m_pRenderTarget(nullptr)
			,m_pRenderPhaseManager(pPhaseMgr)
		{
		}

		CRenderPhase::CRenderPhase(IRenderPhaseManager *pPhaseMgr, int id, int renderTargetFlag)
			:m_pRenderTarget(nullptr)
			,m_pRenderPhaseManager(pPhaseMgr)
			,m_Id(id)
			, m_renderTargetFlag(renderTargetFlag)
		{

		}

		CRenderPhase::~CRenderPhase()
		{
			Destroy();
			for (auto queue : m_renderQueueGroup)
			{
				SAFE_DEL(queue.second);
			}
		}

		void CRenderPhase::Initialize(IRenderer *pRenderer, int width, int height)
		{
			m_pRenderTarget = pRenderer->GetRenderTargetManager()->CreateRenderTarget(m_renderTargetFlag, width, height);
			for (auto queue : m_renderQueueGroup)
			{
				queue.second->BindPhaseUniform();
			}
		}

		void CRenderPhase::Destroy()
		{
			SAFE_DEL(m_pRenderTarget);
		}

		void CRenderPhase::Render()
		{
			if (m_pRenderTarget)
			{
				m_pRenderTarget->BeginTarget();

				for (auto queue : m_renderQueueGroup)
				{
					queue.second->Render();
					queue.second->Clear();
				}
				
				m_pRenderTarget->EndTarget();
			}
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
		IRenderQueue * CRenderPhase::CreateRenderQueue(int materialId)
		{
			IRenderQueue *pRenderQueue = nullptr;
			if (m_renderQueueGroup.find(materialId) == m_renderQueueGroup.end())
			{	
				pRenderQueue = new CRenderQueue(materialId);
				m_renderQueueGroup[materialId] = pRenderQueue;
			}
			return pRenderQueue;
		}

		IRenderQueue * CRenderPhase::GetRenderQueue(int materialId)
		{
			if (m_renderQueueGroup.find(materialId) != m_renderQueueGroup.end())
			{	
				return m_renderQueueGroup[materialId];
			}
			return nullptr;
		}

	}
}