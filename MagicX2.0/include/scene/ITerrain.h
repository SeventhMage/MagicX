#ifndef _MX_SCENE_ITERRAIN_H_
#define _MX_SCENE_ITERRAIN_H_

#include "core/CMatrix4.h"

namespace mx
{
	namespace scene
	{
		class ITerrain
		{
		public:
			ITerrain(){}
			virtual ~ITerrain(){}

			virtual void Update(int elapsedTime, const core::CMatrix4 &mat4MVP, const core::CMatrix4 &mat4MV) = 0;
		};
	}
}

#endif // !_H_TERRAIN_NODE_H_
