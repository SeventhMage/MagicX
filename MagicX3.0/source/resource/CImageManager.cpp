#include "CImageManager.h"
#include "CTGAImage.h"
#include "base/mxString.h"




namespace mx
{
	namespace resource
	{


		CImageManager::CImageManager()
		{

		}

		CImageManager::~CImageManager()
		{

		}

		IResource * CImageManager::LoadResource(const char *filename)
		{
			const char *ext = strrchr(filename, '.');
			if (ext)
			{				
				if (base::ToLower(ext) == ".tga")
				{
					CTGAImage *pImage = new CTGAImage();
					if (pImage)
					{
						if (pImage->Load(filename))
						{
							return pImage;
						}
						else
						{
							delete pImage;
							return nullptr;
						}
					}
				}
			}
			return nullptr;
		}

		void CImageManager::UnLoadResource(IResource *pResource)
		{
			if (pResource)
			{
				delete pResource;
			}
		}

	}
}