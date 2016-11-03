/************************************************************************/
/* ³¡¾°                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_SCENE_H_
#define _MX_SCENE_C_SCENE_H_

#include "scene/IScene.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace scene
	{
		class CScene : public IScene
		{
		public:
			CScene();
			virtual ~CScene();

			virtual ISceneNode *GetRootNode() { return m_pRootNode; }
			virtual void Update(int delta);
			virtual void Draw();
		private:
			ISceneNode *m_pRootNode;
		};
	}
}

#endif