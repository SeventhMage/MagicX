#include "CScreenAlignedQuadManager.h"
#include "CGuassianHBlur.h"
#include "CGuassianVBlur.h"
#include "CIndirectLightMap.h"
#include "CDirectLightMap.h"

namespace mx
{
	namespace render
	{
		CScreenAlignedQuadManager::CScreenAlignedQuadManager()
		{
		}
		CScreenAlignedQuadManager::~CScreenAlignedQuadManager()
		{
		}
		void CScreenAlignedQuadManager::CreateScreenAlignedQuad(const char *name, IRenderQueue *pRenderQuque)
		{
			CScreenAlignedQuad *pQuad = nullptr;
			if (strcmp(name, "ScreenAlignedQuad") == 0)
			{
				pQuad = new CScreenAlignedQuad(pRenderQuque);
			}
			else if (strcmp(name, "IndirectLightMap") == 0)
			{
				pQuad = new CIndirectLightMap(pRenderQuque);
			}
			else if (strcmp(name, "DirectLightMap") == 0)
			{
				pQuad = new CDirectLightMap(pRenderQuque);
			}
			else if (strcmp(name, "GaussianHBlur"))
			{
				pQuad = new CGuassianHBlur(pRenderQuque);
			}
			else if (strcmp(name, "GaussianVBlur"))
			{
				pQuad = new CGuassianVBlur(pRenderQuque);
			}
			if (pQuad)
			{
				m_ScreenAlignedQuadArray.push_back(pQuad);
			}
		}

		void CScreenAlignedQuadManager::Render()
		{
			for (auto pQuad : m_ScreenAlignedQuadArray)
			{
				pQuad->Render();
			}
		}

	}
}