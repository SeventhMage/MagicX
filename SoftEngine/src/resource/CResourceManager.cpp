#include "CResourceManager.h"
#include "CSceneResource.h"
#include "CModel.h"
#include "base/StringHelper.h"


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

			return pResource;
		}

		void CResourceManager::ReleaseResource(IResource *pResource)
		{
			SAFE_DEL(pResource);
		}

	}
}