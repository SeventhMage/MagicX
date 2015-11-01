#include "../include/CSceneManager.h"
#include "CScene.h"
#include "CSkyBox.h"
#include "CTerrainEntity.h"

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
			std::list<ICameraSceneNode *>::iterator itCamera = m_listCamera.begin();
			for (; itCamera != m_listCamera.end(); ++itCamera)
				SAFE_DEL(*itCamera);
			m_listCamera.clear();

			std::list<ISkyBoxSceneNode *>::iterator itSkyBox = m_listSkyBox.begin();
			for (; itSkyBox != m_listSkyBox.end(); ++itSkyBox)
				SAFE_DEL(*itSkyBox);
			m_listSkyBox.clear();

			std::list<ITerrainSceneNode *>::iterator itTerrain = m_listTerrain.begin();
			for (; itTerrain != m_listTerrain.end(); ++itTerrain)
				SAFE_DEL(*itTerrain);
			m_listTerrain.clear();

			std::list<IScene *>::iterator itScene = m_listScene.begin();
			for (; itScene != m_listScene.end(); ++itScene)
				SAFE_DEL(*itScene);
			m_listScene.clear();

		}

		void CSceneManager::Update(uint elapsedTime)
		{
			std::list<IScene *>::iterator itScene = m_listScene.begin();
			for (; itScene != m_listScene.end(); ++itScene)
			{
				if (*itScene)
					(*itScene)->Update(elapsedTime);
			}
		}

		void CSceneManager::Render()
		{
			if (m_pRenderer)
				m_pRenderer->Render();
		}


		IScene *CSceneManager::CreateScene()
		{
			IScene *scene = new CScene(m_pRenderer);
			m_listScene.push_back(scene);
			return scene;
		}

		ITerrainSceneNode *CSceneManager::CreateTerrain(const char * filename)
		{
		
			return NULL;
		}

		ITerrainSceneNode * CSceneManager::CreateRandomTerrain(uint width)
		{
			CTerrainEntity *terrain = new CTerrainEntity(m_pRenderer, width);
			terrain->RandGenerateMesh();
			m_listTerrain.push_back(terrain);
			return terrain;
		}

		IWaterSceneNode *CSceneManager::CreateWater(const char * filename)
		{
			return 0;
		}

		ISkyBoxSceneNode *CSceneManager::CreateSkyBox(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom)
		{
			ISkyBoxSceneNode *skybox = new CSkyBox(m_pRenderer);
			skybox->Create(front, back, left, right, top, bottom);
			m_listSkyBox.push_back(skybox);
			return skybox;
		}

		ICameraSceneNode *CSceneManager::CreateCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip)
		{
			ICameraSceneNode *camera = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
			m_listCamera.push_back(camera);
			return camera;
		}

		void CSceneManager::AddSceneNode(IScene *scene, ISceneNode *sceneNode)
		{
			if (scene && sceneNode)
			{
				scene->AddSceneNode(sceneNode);
			}
		}

		void CSceneManager::RemoveSceneNode(IScene *scene, ISceneNode *sceneNode)
		{
			if (scene && sceneNode)
			{
				scene->RemoveSceneNode(sceneNode);
			}
		}

		void CSceneManager::SetupCamera(IScene *scene, ICameraSceneNode *camera)
		{
			if (scene && camera)
			{
				scene->SetupCamera(camera);
			}
		}

		void CSceneManager::SetupSkyBox(IScene *scene, ISkyBoxSceneNode *skybox)
		{
			if (scene && skybox)
			{
				scene->SetupSkyBox(skybox);
			}
		}

		void CSceneManager::SetupTerrain(IScene *scene, ITerrainSceneNode *terrain)
		{
			if (scene && terrain)
			{
				scene->SetupTerrain(terrain);
			}
		}

		void CSceneManager::DeleteCamera(ICameraSceneNode *camera)
		{
			std::list<ICameraSceneNode *>::iterator it = m_listCamera.begin();
			for (; it != m_listCamera.end(); ++it)
			{
				if (camera == *it)
				{
					m_listCamera.erase(it);
					break;
				}
			}
		}

		void CSceneManager::DeleteSkyBox(ISkyBoxSceneNode *skybox)
		{
			std::list<ISkyBoxSceneNode *>::iterator it = m_listSkyBox.begin();
			for (; it != m_listSkyBox.end(); ++it)
			{
				if (skybox == *it)
				{
					m_listSkyBox.erase(it);
					break;
				}
			}
		}

		void CSceneManager::DeleteTerrain(ITerrainSceneNode *terrain)
		{
			std::list<ITerrainSceneNode *>::iterator it = m_listTerrain.begin();
			for (; it != m_listTerrain.end(); ++it)
			{
				if (terrain == *it)
				{
					m_listTerrain.erase(it);
					break;
				}
			}
		}

		void CSceneManager::DeleteWater(IWaterSceneNode * water)
		{

		}

	}
}