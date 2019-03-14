#include "CRenderPhaseManager.h"
#include "CShadowMapPhase.h"
#include "CSceneGraphPhase.h"
#include "CPostProcessPhase.h"
#include "CSceneOutcomePhase.h"
#include "CGlobalIlluminationPhase.h"
#include "rapidxml.hpp"
#include "mx.h"

#include <fstream>


namespace mx
{
	namespace render
	{
		CRenderPhaseManager::CRenderPhaseManager()
		{
			/*m_vecRenderPhase.push_back(new CGlobalIlluminationPhase(this));
			m_vecRenderPhase.push_back(new CShadowMapPhase(this));
			m_vecRenderPhase.push_back(new CSceneGraphPhase(this));
			m_vecRenderPhase.push_back(new CPostProcessPhase(this));
			m_vecRenderPhase.push_back(new CSceneOutcomePhase(this));*/
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

		void CRenderPhaseManager::LoadRenderPhase(const char *filename)
		{
			char buf[1024] = { 0 };

			std::ifstream infile(filename, std::ios::in);
			if (!infile)
			{
				return;
			}
			infile.read(buf, sizeof(buf));
			rapidxml::xml_document<> doc;
			doc.parse<0>(buf);

			rapidxml::xml_node<> *rootNode = doc.first_node("RenderPhase");
			if (rootNode)
			{
				m_vecRenderPhase.clear();

				for (rapidxml::xml_node<> * node = rootNode->first_node("Pass"); node; node = node->next_sibling())
				{
					int id = atoi(node->first_attribute("id")->value());
					const char *phase = node->first_attribute("phase")->value();
					IRenderPhase *pRenderPhase = CreateRenderPhase(id, phase);
					m_vecRenderPhase.push_back(pRenderPhase);
				}
			}
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
			RENDERER->EndRender();
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

		IRenderPhase * CRenderPhaseManager::CreateRenderPhase(int id, const char *filename)
		{
			char buf[1024] = { 0 };
			std::ifstream infile(filename, std::ios::in);
			if (!infile)
			{
				return nullptr;
			}

			IRenderPhase *pRenderPhase = nullptr;

			infile.read(buf, sizeof(buf));
			rapidxml::xml_document<> doc;
			doc.parse<0>(buf);

			rapidxml::xml_node<> *rootNode = doc.first_node("RenderPhase");
			if (rootNode)
			{
				rapidxml::xml_node<> * renderTargetNode = rootNode->first_node("RenderTarget");
				if (renderTargetNode)
				{
					int flag  = atoi(renderTargetNode->first_attribute("flag")->value());
					pRenderPhase = new CRenderPhase(this, id, flag);

					for (rapidxml::xml_node<> * node = rootNode->first_node("RenderQueue"); node; node = node->next_sibling())
					{
						int id  = atoi(node->first_attribute("materialid")->value());
						const char *name = node->first_attribute("materialname")->value();
						pRenderPhase->CreateRenderQueue(id);
					}

				}
			}
			return pRenderPhase;
		}

	}
}
