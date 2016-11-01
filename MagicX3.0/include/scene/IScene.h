/************************************************************************/
/* 场景结构接口                                                         */
/************************************************************************/

#ifndef _MX_SCENE_I_SCENE_H_
#define _MX_SCENE_I_SCENE_H_

#include "ISceneNode.h"

namespace mx
{
	namespace scene
	{
		class IScene
		{
		public:
			IScene(){};
			virtual~IScene(){};

			//每个场景有唯一根结点，场景图的根
			virtual ISceneNode *GetRootNode() = 0;
		};
	}
}

#endif