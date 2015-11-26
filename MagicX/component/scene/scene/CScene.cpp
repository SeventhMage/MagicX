#include "CScene.h"
#include "CSkyBox.h"
#include "CSceneNode.h"

namespace mx
{
	namespace scene
	{
		CScene::CScene(render::IRenderer *renderer)
			:m_pCamera(NULL)
			,m_pRenderer(renderer)
			, m_pSkyBox(NULL)
		{
			m_pRootNode = new CSceneNode();
		}
		CScene::~CScene()
		{
			if (m_pRootNode)
				m_pRootNode->RemoveAll();
			SAFE_DEL(m_pRootNode);
		}
		void CScene::AddSceneNode(ISceneNode * pSceneNode)
		{
			m_pRootNode->AddChild(pSceneNode);
		}
		void CScene::RemoveSceneNode(ISceneNode * pSceneNode)
		{
		}
		void CScene::RemoveAll()
		{
		}
		bool CScene::LoadScene(const char * filename)
		{
			return false;
		}
		
		
		void CScene::Update(int elapsedTime)
		{
			if (m_pRootNode)
				m_pRootNode->Update(elapsedTime, m_pCamera->GetViewProjectionMatrix(), m_pCamera->GetViewMatrix());
		}

		void CScene::SetupCamera(ICameraSceneNode *camera)
		{
			m_pRootNode->RemoveChild(m_pCamera);
			m_pCamera = camera;
			m_pRootNode->AddChild(m_pCamera);
		}

		void CScene::SetupSkyBox(ISkyBoxSceneNode *skybox)
		{
			m_pRootNode->RemoveChild(m_pSkyBox);
			m_pSkyBox = skybox;
			m_pRootNode->AddChild(m_pSkyBox);
		}

		void CScene::SetupTerrain(ITerrainSceneNode *terrain)
		{
			m_pRootNode->RemoveChild(m_pTerrain);
			m_pTerrain = terrain;
			m_pRootNode->AddChild(m_pTerrain);
		}

	}
}