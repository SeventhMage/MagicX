#include "CScene.h"
#include "CCamera.h"
#include "mx.h"
#include "mxDef.h"
#include "scene/CSceneNode.h"

namespace mx
{
	namespace scene
	{


		CScene::CScene()
			:m_pCamera(nullptr)
		{
			m_pRootNode = new CSceneNode(this);
		}

		CScene::~CScene()
		{
			SAFE_DEL(m_pRootNode);
			SAFE_DEL(m_pCamera);
		}

		void CScene::Draw()
		{
			if (m_pRootNode)
				m_pRootNode->Render();
		}

		void CScene::Update(int delta)
		{
			if (m_pRootNode)
				m_pRootNode->Update(delta);
			if (m_pCamera)
				m_pCamera->Update(delta);
		}

		ICamera *CScene::SetupCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip)
		{
			m_pCamera = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
			return m_pCamera;
		}

		ICamera * CScene::GetCamera()
		{
			return m_pCamera;
		}

	}
}