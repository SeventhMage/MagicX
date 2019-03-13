/************************************************************************/
/* �����ṹ�ӿ�                                                         */
/************************************************************************/

#ifndef _MX_SCENE_I_SCENE_H_
#define _MX_SCENE_I_SCENE_H_

#include "ISceneNode.h"
#include "ICamera.h"
#include "ISkybox.h"
#include "light/ILight.h"

namespace mx
{
	namespace scene
	{
		const int MAX_LIGHT_NUM = 64;
		class IScene
		{
		public:
			IScene(){};
			virtual~IScene(){};

			//ÿ��������Ψһ����㣬����ͼ�ĸ�
			virtual ISceneNode *GetRootNode() = 0;
			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip) = 0;
			virtual void SetupCamera(ICamera *pCamera) = 0;
			virtual ICamera *SetupCamera(float fDistance, ISceneNode *pFocusNode,
				const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip) = 0;
			virtual ICamera *GetCamera() = 0;
			virtual ISkyBox *SetupSkyBox(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back, float radius) = 0;
			virtual ISkyBox *GetSkyBox() = 0;

			//��װ��Դ
			virtual ILight *SetupLight(int slot, ELightType type, float lightColor[4]) = 0;
			virtual ICamera *SetupLightCamera(int slot, const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip) = 0;
			virtual ILight *GetLight(int slot) = 0;
			virtual ICamera *GetLightCamera(int slot) = 0;

			virtual void Update(int delta) = 0;
			virtual void Draw() = 0;
		};
	}
}

#endif