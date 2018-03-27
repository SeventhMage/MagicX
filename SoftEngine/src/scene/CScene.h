#ifndef _SCENE_C_SCENE_H_
#define _SCENE_C_SCENE_H_

#include <string>

#include "render/IRenderQueue.h"
#include "scene/IScene.h"
#include "CSceneNode.h"
#include "CCamera.h"


namespace se
{
	namespace scene
	{
		class CScene : public IScene
		{
		public:
			CScene(const char *name);
			virtual ~CScene();

			//每个场景有唯一根结点，场景图的根
			virtual ISceneNode *GetRootNode(){ return m_pRootNode; }

			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip);
			
			virtual ICamera *SetupCamera(float fDistance, ISceneNode *pFocusNode,
				const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip);
			virtual ICamera *GetCamera();
			virtual ISkyBox *SetupSkyBox(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back, float radius);
			virtual ISkyBox *GetSkyBox() { return nullptr; }

			//安装光源
			virtual ILight *SetupLight(int slot, ELightType type, float lightColor[4]);
			virtual ILight *GetLight(int slot);

			virtual void Update(int delta);			
		private:
			std::string m_strSceneName;
			CSceneNode *m_pRootNode;
			CCamera *m_pCamera;
			ILight *m_pLights[MAX_LIGHT_NUM];
		};
	}
}

#endif