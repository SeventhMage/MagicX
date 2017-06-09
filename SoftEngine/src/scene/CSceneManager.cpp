#include "CSceneManager.h"
#include "CScene.h"

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

	}
}