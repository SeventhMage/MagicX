#ifndef _H_TERRAIN_NODE_H_
#define _H_TERRAIN_NODE_H_

#include "ISceneNode.h"

namespace mx
{
	namespace scene
	{
		class ITerrainSceneNode : public ISceneNode
		{
		public:
			ITerrainSceneNode(){}
			virtual ~ITerrainSceneNode(){}
		};
	}
}

#endif // !_H_TERRAIN_NODE_H_
