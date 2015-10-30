#ifndef _MX_SCENE_I_SKY_BOX_SCENE_NODE_H_
#define _MX_SCENE_I_SKY_BOX_SCENE_NODE_H_

#include "common/mxDef.h"
#include "ISceneNode.h"

namespace mx
{
	namespace scene
	{
		class ISkyBoxSceneNode : public ISceneNode
		{
		public:
			ISkyBoxSceneNode(){}
			virtual ~ISkyBoxSceneNode(){}
			
			virtual bool Create(const char *filename) = 0;
			virtual bool Create(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom)  = 0;
			virtual void UpdateViewProjectMatrix(const CMatrix4 &viewMat4) = 0;
		};
	}
}

#endif // !_I_SKY_BOX_INC_
