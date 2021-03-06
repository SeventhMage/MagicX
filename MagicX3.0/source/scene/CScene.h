/************************************************************************/
/* ����                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_SCENE_H_
#define _MX_SCENE_C_SCENE_H_

#include "scene/IScene.h"

namespace mx
{
	namespace scene
	{
		class CScene : public IScene
		{
		public:
			CScene();
			virtual ~CScene();

			virtual ISceneNode *GetRootNode() { return m_pRootNode; }
			virtual void SetupCamera(ICamera *pCamera){ m_pCamera = pCamera; }
			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip);
			virtual ICamera *SetupCamera(float fDistance, ISceneNode *pFocusNode, 
				const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip);
			virtual ICamera *GetCamera();
			virtual ISkyBox *SetupSkyBox(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back, float radius);
			virtual ISkyBox *GetSkyBox(){ return m_pSkyBox; }
			virtual ILight *SetupLight(int slot, ELightType type, float lightColor[3]);
			virtual ICamera *SetupLightCamera(int slot, const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip);
			virtual ICamera *SetupLightCamera(int slot);
			virtual ILight *GetLight(int slot);
			virtual ICamera *GetLightCamera(int slot);

			virtual void Update(int delta);

		private:
			ISceneNode *m_pRootNode;
			ICamera *m_pCamera;
			ISkyBox *m_pSkyBox;
			ILight *m_pLights[MAX_LIGHT_NUM];
			ICamera *m_pLightCameras[MAX_LIGHT_NUM];
		};
	}
}

#endif