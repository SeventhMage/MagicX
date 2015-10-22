#include "../include/CSceneManager.h"

namespace mx
{
	namespace scene
	{
		CSceneManager::CSceneManager()
		{

		}

		CSceneManager::~CSceneManager()
		{

		}

		void CSceneManager::Update(uint escapeTime)
		{

		}

		void CSceneManager::Render()
		{
			
		}

		IScene * CSceneManager::GetCurrentScene() const
		{
			return m_pCurrentScene;
		}

		const std::list<IScene *> & CSceneManager::GetSceneList() const
		{
			return m_listScene;
		}

		IScene * CSceneManager::CreateScene()
		{
			return nullptr;
		}

	}
}