#ifndef _SCENE_C_SCENE_MANAGER_H_
#define _SCENE_C_SCENE_MANAGER_H_

#include "scene/ISceneManager.h"

namespace mx
{
	class CSceneManager : public ISceneManager
	{
	public:
		CSceneManager();
		~CSceneManager();

		virtual IScene *LoadScene(const char *filename);
		virtual void Update(int delta);
	};
}

#endif