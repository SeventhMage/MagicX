#ifndef _C_TERRAIN_SCENE_NODE_H_
#define _C_TERRAIN_SCENE_NODE_H_

#include "ITerrainSceneNode.h"

namespace mx
{
	namespace scene
	{
		class CTerrainSceneNode : public ITerrainSceneNode
		{
		public:
			CTerrainSceneNode();
			virtual ~CTerrainSceneNode();

			virtual void UpdateImp(uint elapsedTime);
			virtual void RenderImp();
			
			virtual bool LoadTerrain(const char *filename);
		};
	}
}

#endif