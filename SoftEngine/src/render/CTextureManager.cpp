#include "CTextureManager.h"
#include "CSoftEngine.h"
#include "resource/IImage.h"
#include "software/CSoftTexture.h"

namespace se
{
	namespace render
	{

		CTextureManager::CTextureManager()
		{

		}

		CTextureManager::~CTextureManager()
		{
			for (auto it = m_mapTexture.begin(); it != m_mapTexture.end(); ++it)
			{
				ITexture *pTexture = it->second;
				SAFE_DEL(pTexture);
			}
		}

		int CTextureManager::CreateTexture(const char *filename)
		{
			resource::IImage *pImage = dynamic_cast<resource::IImage *>(CSoftEngine::GetResourceManager()->LoadResource(filename));
			if (pImage)
			{
				pImage->GetColorFormat();
				pImage->GetPixelType();

				//xyj----------------------------



				int textureId = m_mapTexture.size() + 1;
				ITexture *pTexture = NULL;
				RenderDriverType driverType = CSoftEngine::GetRenderDriverType();
				switch (driverType)
				{
				case se::render::RDT_SOFTWARE:
					pTexture = new CSoftTexture(textureId);
					break;
				default:
					LogPrint("Unknow render driver type!\n");
					break;
				}
				if (pTexture)
				{
					m_mapTexture[textureId] = pTexture;					
				}
				CSoftEngine::GetResourceManager()->ReleaseResource(pImage);

				return textureId;
			}

			return 0;
		}

		void CTextureManager::DestroyTexture(int textureId)
		{
			auto it = m_mapTexture.find(textureId);
			if (it != m_mapTexture.end())
			{
				m_mapTexture.erase(it);
			}
		}

		ITexture * CTextureManager::GetTexture(int textureId)
		{
			auto it = m_mapTexture.find(textureId);
			if (it != m_mapTexture.end())
			{
				return m_mapTexture[textureId];
			}
			return nullptr;
		}

	}
}