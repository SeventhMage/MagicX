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
			RENDERER->BeginRender();
			for (auto phase : m_vecRenderPhase)
			{
				if (phase)
					phase->Render();
			}
			RENDERER->EndRender();
		}

		IRenderPhase * CRenderPhaseManager::GetRenderPhase(int id)
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
					int width = -1;
					int height = -1;
					if (renderTargetNode->first_attribute("width"))
					{
						width = atoi(renderTargetNode->first_attribute("width")->value());
						height = atoi(renderTargetNode->first_attribute("height")->value());
					}
					pRenderPhase = new CRenderPhase(this, id, flag, width, height);

					for (rapidxml::xml_node<> * node = rootNode->first_node("RenderQueue"); node; node = node->next_sibling())
					{
						int id  = atoi(node->first_attribute("materialid")->value());
						const char *name = node->first_attribute("materialname")->value();
						IRenderQueue *queue = pRenderPhase->CreateRenderQueue(id);

						if (queue)
						{
							for (rapidxml::xml_node<> * quoteNode = node->first_node("PhaseQuote"); quoteNode; quoteNode = quoteNode->next_sibling())
							{
								int quoteid = atoi(quoteNode->first_attribute("id")->value());
								queue->AddPhaseQuote(quoteid);
								for (rapidxml::xml_node<> * uniformNode = quoteNode->first_node("TextureUniform"); uniformNode; uniformNode = uniformNode->next_sibling())
								{
									const char *name = uniformNode->first_attribute("name")->value();
									int slot = atoi(uniformNode->first_attribute("slot")->value());
									int flag = atoi(uniformNode->first_attribute("flag")->value());
									queue->SetPhaseTexture(name, slot, flag);
								}
							}
						}

					}

				}
				rapidxml::xml_node<> * camNode = rootNode->first_node("Camera");
				if (camNode)
				{
					const char *type = camNode->first_attribute("type")->value();
					pRenderPhase->SetCameraType(type);
				}

			}
			return pRenderPhase;
		}

	}
}
