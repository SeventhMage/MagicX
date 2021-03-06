#include "CRenderPhaseManager.h"
#include "CRenderPhase.h"
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
					int textureCount  = atoi(renderTargetNode->first_attribute("texture")->value());
					int depth = atoi(renderTargetNode->first_attribute("depth")->value());
					int width = -1;
					int height = -1;
					float scale = 1.f;
					if (renderTargetNode->first_attribute("width"))
					{
						width = atoi(renderTargetNode->first_attribute("width")->value());
						height = atoi(renderTargetNode->first_attribute("height")->value());
					}

					if (renderTargetNode->first_attribute("scale"))
					{
						scale = atof(renderTargetNode->first_attribute("scale")->value());
					}

					pRenderPhase = new CRenderPhase(this, id, textureCount, width, height, scale, depth == 1);

					for (rapidxml::xml_node<> * node = rootNode->first_node("RenderQueue"); node; node = node->next_sibling())
					{
						int materialid  = atoi(node->first_attribute("materialid")->value());
						IRenderQueue *queue = pRenderPhase->CreateRenderQueue(materialid);

						if (queue)
						{
							const char *name = node->first_attribute("materialname")->value();
							if (node->first_attribute("for"))
							{
								const char *specialfor = node->first_attribute("for")->value();
								RENDERER->GetScreenAlignedQuadManager()->CreateScreenAlignedQuad(specialfor, queue);
							}

							for (rapidxml::xml_node<> * quoteNode = node->first_node("PhaseQuote"); quoteNode; quoteNode = quoteNode->next_sibling())
							{
								int quoteid = atoi(quoteNode->first_attribute("id")->value());
								for (rapidxml::xml_node<> * uniformNode = quoteNode->first_node("TextureUniform"); uniformNode; uniformNode = uniformNode->next_sibling())
								{
									const char *name = uniformNode->first_attribute("name")->value();
									int slot = atoi(uniformNode->first_attribute("slot")->value());
									int index = atoi(uniformNode->first_attribute("index")->value());
									queue->SetPhaseTexture(name, quoteid, slot, index);
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
