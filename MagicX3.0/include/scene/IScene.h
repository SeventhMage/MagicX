/************************************************************************/
/* �����ṹ�ӿ�                                                         */
/************************************************************************/

#ifndef _MX_SCENE_I_SCENE_H_
#define _MX_SCENE_I_SCENE_H_

#include "ISceneNode.h"
#include "ICamera.h"
#include "ISkybox.h"

namespace mx
{
	namespace scene
	{
		class IScene
		{
		public:
			IScene(){};
			virtual~IScene(){};

			//ÿ��������Ψһ����㣬����ͼ�ĸ�
			virtual ISceneNode *GetRootNode() = 0;
			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip) = 0;
			virtual ICamera *SetupCamera(float fDistance, ISceneNode *pFocusNode,
				const CVector3 &vDirection, const CVector3 &vUp, float fov, float aspect, float nearClip, float farClip) = 0;
			virtual ICamera *GetCamera() = 0;
			virtual ISkyBox *SetupSkyBox(const char *front, const char *back, const char *left,
				const char *right, const char *top, const char *bottom, float radius) = 0;
			virtual ISkyBox *GetSkyBox() = 0;
			virtual void Update(int delta) = 0;
			virtual void Draw() = 0;
		};
	}
}

#endif