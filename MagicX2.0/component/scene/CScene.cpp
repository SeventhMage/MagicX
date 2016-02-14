#include "CScene.h"
#include "CSkyBox.h"
#include "CSceneNode.h"

namespace mx
{
	namespace scene
	{
		CScene::CScene()
			:m_pCamera(NULL)
			, m_pSkyBox(NULL)
		{
			m_pRootNode = new CSceneNode();
			m_pRootNode->SetScene(this);

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
			pSceneNode->SetScene(this);
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
			if (m_pCamera)
				m_pCamera->Update(elapsedTime);
			if (m_pSkyBox)
				m_pSkyBox->Update(elapsedTime, m_pCamera->GetViewProjectionMatrix());
			if (m_pTerrain)
				m_pTerrain->Update(elapsedTime, m_pCamera->GetViewProjectionMatrix(), m_pCamera->GetViewMatrix());
			if (m_pRootNode)
				m_pRootNode->Update(elapsedTime);
		}

		void CScene::Render()
		{
			if (m_pRootNode)
				m_pRootNode->Render();
		}

		void CScene::SetupCamera(ICamera *camera)
		{			
			m_pCamera = camera;			
		}

		void CScene::SetupSkyBox(ISkyBox *skybox)
		{			
			m_pSkyBox = skybox;			
		}

		void CScene::SetupTerrain(ITerrain *terrain)
		{			
			m_pTerrain = terrain;			
		}

	}
}