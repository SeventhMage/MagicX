/************************************************************************/
/* �����е�һ��ʵ��                                                     */
/************************************************************************/

#ifndef _MX_SCENE_I_ENTITY_H_
#define _MX_SCENE_I_ENTITY_H_

#include "CSceneNode.h"

namespace mx
{
	namespace scene
	{
		class IEntity : public CSceneNode
		{
		public:
			virtual ~IEntity();
		};
	}
}

#endif