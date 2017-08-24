#ifndef _SE_C_SCENE_MANAGER_H_
#define _SE_C_SCENE_MANAGER_H_

#include "IScene.h"

namespace se
{
	namespace scene
	{
		class ISceneManager
		{
		public:
			virtual ~ISceneManager(){}
			virtual IScene *LoadScene(const char *filename) = 0;
			virtual IScene *GetCurrentScene() = 0;	
			virtual void Update(int delta) = 0;
		};
	}
}

#endif