/************************************************************************/
/* 场景中的一个实体                                                     */
/************************************************************************/

#ifndef _MX_SCENE_C_ENTITY_H_
#define _MX_SCENE_C_ENTITY_H_

#include "CSceneNode.h"

namespace mx
{
	namespace scene
	{
		class CEntity : public CSceneNode
		{
		public:
			CEntity() {}
			virtual ~CEntity(){};
					
		};
	}
}

#endif