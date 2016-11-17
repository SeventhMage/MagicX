#include "CSceneManager.h"
#include "CScene.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{

		CSceneManager::CSceneManager()
		{
			m_pCurrentScene = new CScene();
		}

		CSceneManager::~CSceneManager()
		{
			if (m_pCurrentScene)
				delete m_pCurrentScene;
		}


		void CSceneManager::Update(int delta)
		{
			if (m_pCurrentScene)
			{
				m_pCurrentScene->Update(delta);
			}
		}

		IScene * CSceneManager::LoadScene(const char *filename)
		{			
			return m_pCurrentScene;
		}

		void CSceneManager::Draw()
		{			
			if (m_pCurrentScene)
				m_pCurrentScene->Draw();
		}

	}
}