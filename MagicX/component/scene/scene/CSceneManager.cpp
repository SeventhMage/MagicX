#include "../include/CSceneManager.h"
#include "CScene.h"
#include "CSkyBox.h"

namespace mx
{
	namespace scene
	{
		CSceneManager::CSceneManager(render::IRenderer *renderer)
			:m_pRenderer(renderer)
		{

		}

		CSceneManager::~CSceneManager()
		{
			std::map<uint, IScene *>::iterator itScene = m_mapScene.begin();
			for (; itScene != m_mapScene.end(); ++itScene)
				SAFE_DEL(itScene->second);
			m_mapScene.clear();

			std::map<uint, ISkyBoxSceneNode *>::iterator itSkyBox = m_mapSkyBox.begin();
			for (; itSkyBox != m_mapSkyBox.end(); ++itSkyBox)
				SAFE_DEL(itSkyBox->second);
			m_mapSkyBox.clear();
		}

		void CSceneManager::Update(uint elapsedTime)
		{
			std::map<uint, IScene *>::iterator itScene = m_mapScene.begin();
			for (; itScene != m_mapScene.end(); ++itScene)
			{
				if (itScene->second)
					itScene->second->Update(elapsedTime);
			}
		}

		void CSceneManager::Render()
		{
			if (m_pRenderer)
				m_pRenderer->Render();
		}


		uint CSceneManager::CreateScene()
		{
			IScene *scene = new CScene(m_pRenderer);
			uint key = uint(scene);
			m_mapScene[key] = scene;
			return key;
		}

		uint CSceneManager::CreateTerrain(const char * filename)
		{
			return 0;
		}

		uint CSceneManager::CreateWater(const char * filename)
		{
			return 0;
		}

		uint CSceneManager::CreateSkyBox(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom)
		{
			ISkyBoxSceneNode *skybox = new CSkyBox(m_pRenderer);
			skybox->Create(front, back, left, right, top, bottom);
			uint key = uint(skybox);
			m_mapSkyBox[key] = skybox;
			return key;
		}

		uint CSceneManager::CreateCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip)
		{
			ICameraSceneNode *camera = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
			uint key = uint(camera);
			m_mapCamera[key] = camera;
			return key;
		}

		void CSceneManager::AddSceneNode(uint scene, ISceneNode *sceneNode)
		{
			if (m_mapScene.find(scene) != m_mapScene.end())
			{
				if (m_mapScene[scene])
					m_mapScene[scene]->AddSceneNode(sceneNode);
			}
		}

		void CSceneManager::RemoveSceneNode(uint scene, ISceneNode *sceneNode)
		{
			if (m_mapScene.find(scene) != m_mapScene.end())
			{
				if (m_mapScene[scene])
					m_mapScene[scene]->RemoveSceneNode(sceneNode);
			}
		}

		void CSceneManager::AddWater(uint scene, uint water)
		{

		}

		void CSceneManager::RemoveWater(uint scene, uint water)
		{

		}

		void CSceneManager::SetupCamera(uint scene, uint camera)
		{
			if (m_mapScene.find(scene) != m_mapScene.end() && m_mapCamera.find(camera) != m_mapCamera.end())
			{
				if (m_mapScene[scene] && m_mapCamera[camera])
				{
					m_mapScene[scene]->SetupCamera(m_mapCamera[camera]);
				}
			}
		}

		void CSceneManager::SetupSkyBox(uint scene, uint skybox)
		{
			if (m_mapScene.find(scene) != m_mapScene.end() && m_mapSkyBox.find(skybox) != m_mapSkyBox.end())
			{
				if (m_mapScene[scene] && m_mapSkyBox[skybox])
				{
					m_mapScene[scene]->SetupSkyBox(m_mapSkyBox[skybox]);
				}
			}
		}

		void CSceneManager::SetupTerrain(uint scene, uint terrain)
		{
			if (m_mapScene.find(scene) != m_mapScene.end() && m_mapCamera.find(terrain) != m_mapCamera.end())
			{
				if (m_mapScene[scene] && m_mapTerrain[terrain])
				{
					m_mapScene[scene]->SetupTerrain(m_mapTerrain[terrain]);
				}
			}
		}

		void CSceneManager::DeleteCamera(uint camera)
		{
			m_mapCamera.erase(camera);
		}

		void CSceneManager::DeleteSkyBox(uint skybox)
		{
			m_mapSkyBox.erase(skybox);
		}

		void CSceneManager::DeleteTerrain(uint terrain)
		{
			m_mapTerrain.erase(terrain);
		}

	}
}