#include "resource/CMeshManager.h"
#include "resource/CMesh.h"

namespace mx
{
	namespace resource
	{

		CMeshManager::CMeshManager(render::IRenderer *pRenderer)
			:m_pRenderer(pRenderer)
		{
			m_pGPUBuffer = m_pRenderer->CreateGPUBuffer();
		}

		CMeshManager::~CMeshManager()
		{

		}

		IResource * CMeshManager::CreateResource(const char *filename)
		{
			IMesh *pMesh = new CMesh(m_pGPUBuffer);
			pMesh->Load(filename);
			return pMesh;
		}

	}
}