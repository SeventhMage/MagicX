#include "resource/CMeshManager.h"
#include "resource/CMesh.h"

namespace mx
{
	namespace resource
	{

		CMeshManager::CMeshManager()
		{
		}

		CMeshManager::~CMeshManager()
		{

		}

		IResource * CMeshManager::CreateResource(const char *filename)
		{
			IMesh *pMesh = new CMesh();
			pMesh->Load(filename);
			return pMesh;
		}

	}
}