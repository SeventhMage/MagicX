#include "CScene.h"
#include "CSkyBox.h"
#include "CSceneNode.h"

namespace mx
{
	namespace scene
	{
		CScene::CScene(render::IRenderer *renderer)
			:m_pCamera(NULL)
			,m_pSkyBox(NULL)
			,m_pRenderer(renderer)
		{
			m_pRootNode = new CSceneNode();
		}
		CScene::~CScene()
		{
			SAFE_DEL(m_pCamera);
			SAFE_DEL(m_pSkyBox);

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
		
		ISkyBox * CScene::CreateSkyBox(const char * filename)
		{
			return nullptr;
		}
		ISkyBox * CScene::CreateSkyBox(const char * front, const char * back, const char * left, const char * right, const char * top, const char * bottom)
		{
			SAFE_DEL(m_pSkyBox);
			m_pSkyBox = new CSkyBox(m_pRenderer);
			m_pSkyBox->Create(front, back, left, right, top, bottom);
			return m_pSkyBox;
		}
	
		ICamera * CScene::SetupCamera(const CVector3 & position, const CVector3 & direction, const CVector3 & up, float fov, float aspect, float nearClip, float farClip)
		{
			m_pCamera = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
			return m_pCamera;
		}
		void CScene::Update(int elapsedTime)
		{
			if (m_pSkyBox)
				m_pSkyBox->Update(m_pCamera->GetViewProjectionMatrix(), elapsedTime);
			if (m_pRootNode)
				m_pRootNode->Update(elapsedTime);
		}
		void CScene::Render()
		{
			if (m_pRootNode)
				m_pRootNode->Render();
		}
	}
}