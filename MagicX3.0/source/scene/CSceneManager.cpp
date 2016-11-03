#include "CSceneManager.h"

namespace mx
{
	namespace scene
	{

		CSceneManager::CSceneManager()
			:m_pCurrentScene(NULL)
		{

		}

		CSceneManager::~CSceneManager()
		{

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
			return nullptr;
		}

		void CSceneManager::Draw()
		{
			if (m_pCurrentScene)
				m_pCurrentScene->Draw();
		}

	}
}