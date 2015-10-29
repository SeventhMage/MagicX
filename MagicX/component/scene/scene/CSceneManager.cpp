#include "../include/CSceneManager.h"
#include "CScene.h"

namespace mx
{
	namespace scene
	{
		CSceneManager::CSceneManager()
		{

		}

		CSceneManager::~CSceneManager()
		{
			std::list<IScene *>::iterator it = m_listScene.begin();
			for (; it != m_listScene.end(); ++it)
				SAFE_DEL(*it);
			m_listScene.clear();
		}

		void CSceneManager::Update(uint elapsedTime)
		{
			std::list<IScene *>::iterator it = m_listScene.begin();
			for (; it != m_listScene.end(); ++it)
				if (*it)
					(*it)->Update(elapsedTime);
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

		IScene * CSceneManager::CreateScene(render::IRenderer * renderer)
		{
			m_pCurrentScene = new CScene(renderer);
			m_listScene.push_back(m_pCurrentScene);
			return m_pCurrentScene;
		}

		ITerrainSceneNode * CSceneManager::CreateTerrain(const char * filename)
		{
			return nullptr;
		}

		IWaterSceneNode * CSceneManager::CreateWater(const char * filename)
		{
			return nullptr;
		}
	}
}