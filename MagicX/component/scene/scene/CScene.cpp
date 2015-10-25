#include "CScene.h"
#include "CSkyBox.h"

namespace mx
{
	namespace scene
	{
		CScene::CScene(render::IRenderer *renderer)
			:m_pCamera(NULL)
			,m_pSkyBox(NULL)
			,m_pRenderer(renderer)
		{
		}
		CScene::~CScene()
		{
			SAFE_DEL(m_pCamera);
			SAFE_DEL(m_pSkyBox);
		}
		void CScene::AddSceneNode(ISceneNode * pSceneNode)
		{
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
		ITerrainSceneNode * CScene::CreateTerrain(const char * filename)
		{
			return nullptr;
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
		}
		void CScene::Render()
		{

		}
	}
}