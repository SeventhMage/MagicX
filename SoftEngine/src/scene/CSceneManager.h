#ifndef _C_SCENE_MANAGER_H_
#define _C_SCENE_MANAGER_H_

#include "scene/ISceneManager.h"
#include "scene/IScene.h"
#include "base/CSingleton.h"

namespace se
{
	namespace scene
	{
		class CSceneManager : public ISceneManager, public base::CSingleton<CSceneManager>
		{
		public:
			CSceneManager();
			virtual ~CSceneManager();

			virtual IScene *LoadScene(const char *filename);
			virtual IScene *GetCurrentScene(){ return m_pCurrentScene; }
			virtual void Update(int delta);
		private:
			IScene *m_pCurrentScene;			
		};
	}
}

#endif