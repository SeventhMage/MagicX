#include "CRenderPhaseManager.h"
#include "CShadowMapPhase.h"
#include "CSceneGraphPhase.h"
#include "CPostProcessPhase.h"
#include "CSceneOutcomePhase.h"


namespace mx
{
	namespace render
	{
		CRenderPhaseManager::CRenderPhaseManager()
		{
			//m_vecRenderPhase.push_back(new CShadowMapPhase());
			//m_vecRenderPhase.push_back(new CSceneGraphPhase());
			//m_vecRenderPhase.push_back(new CPostProcessPhase());
			m_vecRenderPhase.push_back(new CSceneOutcomePhase());
		}

		CRenderPhaseManager::~CRenderPhaseManager()
		{
			for (auto phase : m_vecRenderPhase)
			{
				if (phase)
					delete phase;
			}
			m_vecRenderPhase.clear();
		}

		void CRenderPhaseManager::Initialize(IRenderer *pRenderer, int width, int height)
		{
			for (auto phase : m_vecRenderPhase)
			{
				if (phase)
					phase->Initialize(pRenderer, width, height);
			}
		}

		void CRenderPhaseManager::ProcessRenderPhase()
		{
			for (auto phase : m_vecRenderPhase)
			{
				if (phase)
					phase->Render();
			}
		}

		IRenderPhase * CRenderPhaseManager::GetRenderPhase(ERenderPhaseID id)
		{
			for (auto phase : m_vecRenderPhase)
			{
				if (phase && phase->GetPhaseID() == id)
					return phase;
			}
			return nullptr;
		}

	}
}
