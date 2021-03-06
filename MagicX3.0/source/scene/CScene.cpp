#include "CScene.h"
#include "CCamera.h"
#include "mx.h"
#include "mxDef.h"
#include "scene/CSceneNode.h"
#include "CSkyBox.h"
#include "scene/light/CDirectionalLight.h"
#include "scene/light/CPointLight.h"
#include "scene/light/CSpotLight.h"
#include "scene/light/CAmbientLight.h"

namespace mx
{
	namespace scene
	{


		CScene::CScene()
			:m_pCamera(nullptr)
			, m_pSkyBox(nullptr)
		{
			m_pRootNode = new CSceneNode();
			memset(m_pLights, 0, sizeof(m_pLights));
			memset(m_pLightCameras, 0, sizeof(m_pLightCameras));
		}

		CScene::~CScene()
		{
			SAFE_DEL(m_pSkyBox);
			SAFE_DEL(m_pRootNode);
			SAFE_DEL(m_pCamera);
			for (int i = 0; i < MAX_LIGHT_NUM; ++i)
			{	
				SAFE_DEL(m_pLights[i]);
				SAFE_DEL(m_pLightCameras[i]);
			}
		}

		void CScene::Update(int delta)
		{
			if (m_pCamera)
				m_pCamera->Update(delta);
			for (int i = 0; i < MAX_LIGHT_NUM; ++i)
			{
				if (m_pLightCameras[i])
					m_pLightCameras[i]->Update(delta);
				else
					break;
			}
			if (m_pRootNode)
				m_pRootNode->Update(delta);

		}

		ICamera *CScene::SetupCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip)
		{
			SAFE_DEL(m_pCamera);
			m_pCamera = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
			return m_pCamera;
		}

		ICamera * CScene::SetupCamera(float fDistance, ISceneNode *pFocusNode, const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip)
		{
			SAFE_DEL(m_pCamera);
			m_pCamera = new CCamera(fDistance, pFocusNode, vDirection, vUp, fov, aspect, nearClip, farClip);
			return m_pCamera;
		}

		ICamera * CScene::GetCamera()
		{
			return m_pCamera;
		}

		ISkyBox * CScene::SetupSkyBox(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back, float radius)
		{
			SAFE_DEL(m_pSkyBox);
			m_pSkyBox = new CSkyBox(this, radius);
			m_pSkyBox->Create(right, left, top, bottom, front, back);
			return m_pSkyBox;
		}

		ILight * CScene::SetupLight(int slot, ELightType type, float lightColor[3])
		{
			if (slot < 0 || slot > MAX_LIGHT_NUM)
				return nullptr;
			if (m_pLights[slot])
				delete m_pLights[slot];
			switch (type)
			{
			case mx::scene::LT_DIRECTIONAL:
				m_pLights[slot] = new CDirectionalLight(lightColor);
				break;
			case mx::scene::LT_POINT:
				m_pLights[slot] = new CPointLight(lightColor);
				break;
			case mx::scene::LT_AMBIENT:
				m_pLights[slot] = new CAmbientLight(lightColor);
			case mx::scene::LT_SPOT:
				//m_pLights[slot] = new CSpotLight();
				break;
			default:
				break;
			}
			return m_pLights[slot];
		}

		ICamera * CScene::SetupLightCamera(int slot, const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip)
		{
			SAFE_DEL(m_pLightCameras[slot]);
			switch (m_pLights[slot]->GetLightType())
			{
			case LT_POINT:
				m_pLightCameras[slot] = new CCamera(position, direction, up, fov, aspect, nearClip, farClip);
				break;
			case LT_DIRECTIONAL:
				m_pLightCameras[slot] = new CCamera(position, direction, up, fov, aspect, nearClip, farClip, true);
				break;

			}
			return m_pLightCameras[slot];
		}

		ICamera * CScene::SetupLightCamera(int slot)
		{
			if (slot >= 0 &&slot < MAX_LIGHT_NUM)
				m_pLightCameras[slot] = new CCamera();
			return m_pLightCameras[slot];
		}

		ILight * CScene::GetLight(int slot)
		{
			if (slot < 0 || slot > MAX_LIGHT_NUM)
				return nullptr;
			return m_pLights[slot];
		}

		ICamera * CScene::GetLightCamera(int slot)
		{
			if (slot < 0 || slot > MAX_LIGHT_NUM)
				return nullptr;
			return m_pLightCameras[slot];
		}


	}
}