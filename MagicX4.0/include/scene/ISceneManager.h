#ifndef _SCENE_I_SCENE_MANAGER_H_
#define _SCENE_I_SCENE_MANAGER_H_

#include "IScene.h"

namespace mx
{
	class ISceneManager
	{
	public:
		virtual IScene *LoadScene(const char *filename) = 0;
		virtual void Update(int delta) = 0;
	};
}

#endif