#ifndef _MX_SCENE_C_SCENE_NODE_H_
#define _MX_SCENE_C_SCENE_NODE_H_

#include "scene/ISceneNode.h"

namespace mx
{
	namespace scene
	{
		class CSceneNode : public ISceneNode
		{
		public:
			CSceneNode();
			virtual ~CSceneNode();

			virtual void UpdateImp(int elapsedTime) {}
			virtual void RenderImp(){}
		};
	}
}

#endif
