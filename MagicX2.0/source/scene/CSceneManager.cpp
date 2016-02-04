#include "scene/CSceneManager.h"
#include "scene/CScene.h"
#include "scene/CSkyBox.h"
#include "scene/CRandomTerrain.h"

namespace mx
{
	namespace scene
	{
		CSceneManager::CSceneManager(render::IRenderer *pRenderer)
			:m_pRenderer(pRenderer)
		{

		}

		CSceneManager::~CSceneManager()
		{
			std::list<ICamera *>::iterator itCamera = m_listCamera.begin();
			for (; itCamera != m_listCamera.end(); ++itCamera)
				SAFE_DEL(*itCamera);
			m_listCamera.clear();

			std::list<ISkyBox *>::iterator itSkyBox = m_listSkyBox.begin();
			for (; itSkyBox != m_listSkyBox.end(); ++itSkyBox)
				SAFE_DEL(*itSkyBox);
			m_listSkyBox.clear();

			std::list<ITerrain *>::iterator itTerrain = m_listTerrain.begin();
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

		IScene *CSceneManager::CreateScene()
		{
			IScene *scene = new CScene();
			m_listScene.push_back(scene);
			return scene;
		}

		ITerrain *CSceneManager::CreateTerrain(const char * filename)
		{
		
			return NULL;
		}

		ITerrain * CSceneManager::CreateRandomTerrain(uint width)
		{
			CRandomTerrain *terrain = new CRandomTerrain(m_pRenderer, width);
			terrain->RandGenerateMesh();
			m_listTerrain.push_back(terrain);
			return terrain;
		}

		IWater *CSceneManager::CreateWater(const char * filename)
		{
			return 0;
		}

		ISkyBox *CSceneManager::CreateSkyBox(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom, float radius)
		{
			ISkyBox *skybox = new CSkyBox(m_pRenderer, radius);
			skybox->Create(front, back, left, right, top, bottom);
			m_listSkyBox.push_back(skybox);
			return skybox;
		}

		ICamera *CSceneManager::CreateCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip)
		{
			ICamera *camera = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
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

		void CSceneManager::SetupCamera(IScene *scene, ICamera *camera)
		{
			if (scene && camera)
			{
				scene->SetupCamera(camera);
			}
		}

		void CSceneManager::SetupSkyBox(IScene *scene, ISkyBox *skybox)
		{
			if (scene && skybox)
			{
				scene->SetupSkyBox(skybox);
			}
		}

		void CSceneManager::SetupTerrain(IScene *scene, ITerrain *terrain)
		{
			if (scene && terrain)
			{
				scene->SetupTerrain(terrain);
			}
		}

		void CSceneManager::DeleteCamera(ICamera *camera)
		{
			std::list<ICamera *>::iterator it = m_listCamera.begin();
			for (; it != m_listCamera.end(); ++it)
			{
				if (camera == *it)
				{
					m_listCamera.erase(it);
					break;
				}
			}
		}

		void CSceneManager::DeleteSkyBox(ISkyBox *skybox)
		{
			std::list<ISkyBox *>::iterator it = m_listSkyBox.begin();
			for (; it != m_listSkyBox.end(); ++it)
			{
				if (skybox == *it)
				{
					m_listSkyBox.erase(it);
					break;
				}
			}
		}

		void CSceneManager::DeleteTerrain(ITerrain *terrain)
		{
			std::list<ITerrain *>::iterator it = m_listTerrain.begin();
			for (; it != m_listTerrain.end(); ++it)
			{
				if (terrain == *it)
				{
					m_listTerrain.erase(it);
					break;
				}
			}
		}

		void CSceneManager::DeleteWater(IWater * water)
		{

		}

	}
}