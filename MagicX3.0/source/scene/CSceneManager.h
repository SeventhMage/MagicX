/************************************************************************/
/* ≥°æ∞π‹¿Ì∆˜                                                           */
/************************************************************************/

#ifndef _MX_SCENE_C_SCENE_MANAGER_H_
#define _MX_SCENE_C_SCENE_MANAGER_H_

#include "scene/ISceneManager.h"

namespace mx
{
	namespace scene
	{
		class CSceneManager : public ISceneManager
		{
		public:
			CSceneManager();
			virtual ~CSceneManager();

			virtual void Update(int delta);
			virtual IScene *LoadScene(const char *filename);
			virtual IScene *GetCurrentScene() { return m_pCurrentScene; }
			virtual void Draw();
		private:
			IScene *m_pCurrentScene;
		};
	}
}

#endif