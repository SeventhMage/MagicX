/************************************************************************/
/* ³¡¾°½áµã                                                             */
/************************************************************************/

#ifndef MX_SCENE_C_SCENE_NODE_H_
#define MX_SCENE_C_SCENE_NODE_H_

#include "scene/ISceneNode.h"

#include <list>

namespace mx
{
	namespace scene
	{
		class CSceneNode : public ISceneNode
		{
		public:
			CSceneNode();
			virtual ~CSceneNode();

			virtual void UpdateImp(int delta);
			virtual void RenderImp();
		};
	}
}

#endif
