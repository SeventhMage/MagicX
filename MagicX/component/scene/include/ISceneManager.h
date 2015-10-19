#ifndef _I_SCENE_MANAGER_H_INC_
#define _I_SCENE_MANAGER_H_INC_

#include <list>

#include "ISceneNode.h"
#include "IScene.h"
#include "common/mxDef.h"

namespace mx
{
	namespace scene
	{
		class ISceneManager
		{
		public:
			ISceneManager(){}
			virtual ~ISceneManager(){}

			virtual void Update() = 0;
			virtual void Render() = 0;			

			virtual IScene *CreateScene(const char *filename) = 0;
			virtual IScene *CloseCurrentScene() = 0;
			virtual IScene *GetCurrentScene() = 0;
			virtual const std::list<IScene *> &GetSceneList() = 0;
		};
	}
}

#endif // !_I_SCENE_MANAGER_H_INC_
