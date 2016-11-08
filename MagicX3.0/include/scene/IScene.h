/************************************************************************/
/* 场景结构接口                                                         */
/************************************************************************/

#ifndef _MX_SCENE_I_SCENE_H_
#define _MX_SCENE_I_SCENE_H_

#include "ISceneNode.h"
#include "ICamera.h"

namespace mx
{
	namespace scene
	{
		class IScene
		{
		public:
			IScene(){};
			virtual~IScene(){};

			//每个场景有唯一根结点，场景图的根
			virtual ISceneNode *GetRootNode() = 0;
			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip) = 0;
			virtual ICamera *GetCamera() = 0;
			virtual void Update(int delta) = 0;
			virtual void Draw() = 0;
		};
	}
}

#endif