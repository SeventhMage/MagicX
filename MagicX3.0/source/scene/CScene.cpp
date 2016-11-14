#include "CScene.h"
#include "CCamera.h"
#include "mx.h"
#include "mxDef.h"
#include "scene/CSceneNode.h"
#include "CSkyBox.h"

namespace mx
{
	namespace scene
	{


		CScene::CScene()
			:m_pCamera(nullptr)
			, m_pSkyBox(nullptr)
		{
			m_pRootNode = new CSceneNode(this);
		}

		CScene::~CScene()
		{
			SAFE_DEL(m_pRootNode);
			SAFE_DEL(m_pCamera);
			SAFE_DEL(m_pSkyBox);
		}

		void CScene::Draw()
		{
			if (m_pRootNode)
				m_pRootNode->Render();
			if (m_pSkyBox)
				m_pSkyBox->Render();
		}

		void CScene::Update(int delta)
		{
			if (m_pCamera)
				m_pCamera->Update(delta);
			if (m_pSkyBox)
				m_pSkyBox->Update(delta);
			if (m_pRootNode)
				m_pRootNode->Update(delta);

		}

		ICamera *CScene::SetupCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip)
		{
			m_pCamera = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
			return m_pCamera;
		}

		ICamera * CScene::SetupCamera(float fDistance, ISceneNode *pFocusNode, const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip)
		{
			m_pCamera = new CCamera(fDistance, pFocusNode, vDirection, vUp, fov, aspect, nearClip, farClip);
			return m_pCamera;
		}

		ICamera * CScene::GetCamera()
		{
			return m_pCamera;
		}

		ISkyBox * CScene::SetupSkyBox(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back, float radius)
		{
			m_pSkyBox = new CSkyBox(this, radius);
			m_pSkyBox->Create(right, left, top, bottom, front, back);
			return m_pSkyBox;
		}

	}
}