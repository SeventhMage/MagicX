#include "CScene.h"

namespace mx
{
	namespace scene
	{
		CScene::CScene()
			:m_camera(NULL)
		{
		}
		CScene::~CScene()
		{
			SAFE_DEL(m_camera);
		}
		void CScene::AddSceneNode(ISceneNode * pSceneNode)
		{
		}
		void CScene::RemoveSceneNode(ISceneNode * pSceneNode)
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
		ITerrainSceneNode * CScene::CreateTerrain(const char * filename)
		{
			return nullptr;
		}
		ICamera * CScene::SetupCamera(const CVector3 & position, const CVector3 & direction, const CVector3 & up)
		{
			m_camera = new CCamera(position, direction, up);
			return m_camera;
		}
		void CScene::Render()
		{
		}
	}
}