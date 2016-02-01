#ifndef _C_SCENE_MANAGER_H_
#define _C_SCENE_MANAGER_H_

#include "core/CSingleton.h"
#include "render/IRenderer.h"


#include <list>

namespace mx
{
	namespace scene
	{
		class CSceneManager
		{
		public:
			CSceneManager(render::IRenderer *renderer);
			virtual ~CSceneManager();



		private:			
			render::IRenderer *m_pRenderer;
		};
	}
}

#endif