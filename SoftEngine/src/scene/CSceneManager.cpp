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

		}

		CSceneManager::~CSceneManager()
		{
			SAFE_DEL(m_pCurrentScene);
		}

		IScene * CSceneManager::LoadScene(const char *filename)
		{			
			SAFE_DEL(m_pCurrentScene);
			m_pCurrentScene = new CScene(filename);
			return m_pCurrentScene;
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
					m_renderQueueGroup
				}
			}
		}

	}
}