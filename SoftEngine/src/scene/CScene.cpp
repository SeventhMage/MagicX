#include "CScene.h"

#include "CSoftEngine.h"
#include "base/seDef.h"
#include "resource/ISceneResource.h"
#include "light/CPointLight.h"
namespace se
{
	namespace scene
	{


		CScene::CScene(const char *name)
			:m_strSceneName(name)
			, m_pCamera(nullptr)
			, m_pRootNode(new CSceneNode(this))			
		{
			memset(m_pLights, 0, sizeof(ILight *)* MAX_LIGHT_NUM);

			resource::ISceneResource *pResource = dynamic_cast<resource::ISceneResource *>(CSoftEngine::GetResourceManager()->LoadResource(m_strSceneName.c_str()));
			if (pResource)
			{
				float aspect = CSoftEngine::GetDevice()->GetWindowWidth() * 1.0f / CSoftEngine::GetDevice()->GetWindowHeight();
				resource::SCameraParam cameraParam = pResource->GetCameraParam();
				SetupCamera(cameraParam.position, cameraParam.direction, cameraParam.up, DEG_TO_RAD(cameraParam.fov),
					aspect, cameraParam.nearClip, cameraParam.farClip);

				int entityCount = pResource->GetEntityCount();
				for (int i = 0; i < entityCount; ++i)
				{
					resource::SEntityInfo entity = pResource->GetEntityInfoByIdx(i);					
					CSceneNode *pNode = new CSceneNode(entity.name, this);
					pNode->SetPosition(entity.position);
					m_pRootNode->AddChildNode(pNode);
				}

				CSoftEngine::GetResourceManager()->ReleaseResource(pResource);
			}
		}

		CScene::~CScene()
		{
			SAFE_DEL(m_pCamera);
			SAFE_DEL(m_pRootNode);
		}
		void CScene::Update(int delta)
		{
			if (m_pCamera)
				m_pCamera->Update(delta);
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
			return nullptr;
		}

		ILight * CScene::SetupLight(int slot, ELightType type, float lightColor[4])
		{
			if (slot < 0 || slot > MAX_LIGHT_NUM)
				return nullptr;
			if (m_pLights[slot])
				delete m_pLights[slot];
			switch (type)
			{
			case se::scene::LT_DIRECTIONAL:
				//m_pLights[slot] = new CDirectionalLight();
				break;
			case se::scene::LT_POINT:
				m_pLights[slot] = new CPointLight(lightColor);
				break;
			case se::scene::LT_SPOT:
				//m_pLights[slot] = new CSpotLight();
				break;
			default:
				break;
			}
			return m_pLights[slot];
		}

		ILight * CScene::GetLight(int slot)
		{
			if (slot < 0 || slot > MAX_LIGHT_NUM)
				return nullptr;
			return m_pLights[slot];
		}

	}
}