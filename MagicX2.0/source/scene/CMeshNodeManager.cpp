#include "scene/CMeshNodeManager.h"

namespace mx
{
	namespace scene
	{

		CMeshNodeManager::CMeshNodeManager(IRenderer *pRenderer)
			:m_pRenderer(pRenderer)
		{
			m_pRenderer->Increase();
			m_pGPUBuffer = m_pRenderer->CreateGPUBuffer();
		}

		CMeshNodeManager::~CMeshNodeManager()
		{
			MeshTable::iterator it = m_tbMeshNode.begin();
			for (; it != m_tbMeshNode.end(); ++it)
			{
				if (*it)
				{
					delete *it;
				}
			}
			m_tbMeshNode.clear();
			m_pRenderer->DestroyGPUBuffer(m_pGPUBuffer);
			m_pRenderer->Decrease();
		}

		CMeshNode *CMeshNodeManager::CreateMeshNode(resource::IMesh *pMesh)
		{
			CMeshNode *pMeshNode = new CMeshNode(pMesh, m_pGPUBuffer);
			m_tbMeshNode.push_back(pMeshNode);
			return pMeshNode;
		}

		void CMeshNodeManager::DestroyMeshNode(CMeshNode *pMeshNode)
		{
			MeshTable::iterator it = m_tbMeshNode.begin();
			for (; it != m_tbMeshNode.end(); ++it)
			{
				if (*it == pMeshNode)
				{					
					m_tbMeshNode.erase(it);
					delete pMeshNode;
					break;
				}
			}
		}

	}
}