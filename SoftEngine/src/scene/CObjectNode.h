#ifndef _SCENE_C_OBJECT_NODE_H_
#define _SCENE_C_OBJECT_NODE_H_

#include "CSceneNode.h"

namespace se
{
	namespace scene
	{
		class CObjectNode : public CSceneNode
		{
		public:
			CObjectNode(IScene *pScene, uint objID);
			virtual ~CObjectNode();

			virtual void Update(int delta);
		private:
			uint m_ObjectID;
		};
	}
}

#endif