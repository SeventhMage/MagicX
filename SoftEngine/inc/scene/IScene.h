#ifndef _SE_I_SCENE_H_
#define _SE_I_SCENE_H_

#include "math/CVector3.h"
#include "ISceneNode.h"
#include "ICamera.h"
#include "ISkyBox.h"
#include "ILight.h"



namespace se
{
	namespace scene
	{
		const int MAX_LIGHT_NUM = 16;
		using namespace math;
		class IScene
		{
		public:
			IScene(){};
			virtual~IScene(){};

			//每个场景有唯一根结点，场景图的根
			virtual ISceneNode *GetRootNode() = 0;

			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip) = 0;			
			virtual ICamera *SetupCamera(float fDistance, ISceneNode *pFocusNode,
				const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip) = 0;
			virtual ICamera *GetCamera() = 0;
			virtual ISkyBox *SetupSkyBox(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back, float radius) = 0;
			virtual ISkyBox *GetSkyBox() = 0;

			//安装光源
			virtual ILight *SetupLight(int slot, ELightType type, float lightColor[4]) = 0;
			virtual ILight *GetLight(int slot) = 0;

			virtual void Update(int delta) = 0;			
		};
	}
}

#endif