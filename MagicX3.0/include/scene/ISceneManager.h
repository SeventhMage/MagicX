/************************************************************************/
/* 场景管理器接口                                                       */
/************************************************************************/
#ifndef _MX_SCENE_I_SCENE_MANAGER_H_
#define _MX_SCENE_I_SCENE_MANAGER_H_

#include "IScene.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace scene
	{
		class ISceneManager
		{
		public:
			ISceneManager(){};
			virtual ~ISceneManager(){};
			
			//场景更新
			virtual void Update(int delta) = 0;

			//通过文件载入场景
			virtual IScene *LoadScene(const char *filename) = 0;

			//返回当前场景
			virtual IScene *GetCurrentScene() = 0;

		};
	}
}

#endif