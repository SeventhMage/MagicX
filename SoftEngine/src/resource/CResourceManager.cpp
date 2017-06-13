#include "base/StringHelper.h"
#include "CResourceManager.h"
#include "CSceneResource.h"
#include "CMaterialResource.h"
#include "CModel.h"



namespace se
{
	namespace resource
	{


		IResource * CResourceManager::LoadResource(const char *filename)
		{
			IResource *pResource = nullptr;
			std::string extName = base::GetFileExtName(filename);
			if (extName == "scene")
			{
				pResource = new CSceneResource(filename);
			}
			else if (extName == "obj")
			{
				pResource = new CModel(filename);
			}
			else if (extName == "mlt")
			{
				pResource = new CMaterialResource(filename);
			}

			return pResource;
		}

		void CResourceManager::ReleaseResource(IResource *pResource)
		{
			SAFE_DEL(pResource);
		}

	}
}