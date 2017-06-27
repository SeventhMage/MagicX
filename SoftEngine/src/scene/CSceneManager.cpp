#include "CSceneManager.h"
#include "CScene.h"
#include "CSoftEngine.h"
#include "resource/IMaterialResource.h"

namespace se
{
	namespace scene
	{

		CSceneManager::CSceneManager()
			:m_pCurrentScene(nullptr)
		{
			LoadMaterial();
		}

		CSceneManager::~CSceneManager()
		{
			SAFE_DEL(m_pCurrentScene);
			for (auto it = m_renderQueueGroup.begin(); it != m_renderQueueGroup.end(); ++it)
			{
				CSoftEngine::GetRenderer()->DestroyRenderQueue(*it);
			}
		}

		void CSceneManager::LoadMaterial()
		{
			resource::IMaterialResource *pResource = dynamic_cast<resource::IMaterialResource *>
				(CSoftEngine::GetResourceManager()->LoadResource("materialgroup.mtl"));
			if (pResource)
			{
				for (int i = 0; i < pResource->GetAttrCount(); ++i)
				{
					std::string materialName = pResource->GetValueByIdx(i);
					resource::IMaterialResource *pMaterialRes = dynamic_cast<resource::IMaterialResource *>
						(CSoftEngine::GetResourceManager()->LoadResource(materialName.c_str()));					
					render::IRenderQueue *pRenderQueue = CSoftEngine::GetRenderer()->CreateRenderQueue(materialName.c_str());
					m_renderQueueGroup.push_back(pRenderQueue);
				}
				CSoftEngine::GetResourceManager()->ReleaseResource(pResource);
			}

		}

		IScene * CSceneManager::LoadScene(const char *filename)
		{
			SAFE_DEL(m_pCurrentScene);
			m_pCurrentScene = new CScene(filename);
			return m_pCurrentScene;
		}

	}
}