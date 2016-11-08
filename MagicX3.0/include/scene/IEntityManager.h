/************************************************************************/
/* 实体管理器接口                                                       */
/************************************************************************/

#ifndef _MX_I_SCENE_I_ENTITY_MANAGER_H_
#define _MX_I_SCENE_I_ENTITY_MANAGER_H_

#include "CEntity.h"
#include "IVertex.h"

namespace mx
{
	namespace scene
	{
		class IEntityManager
		{
		public:
			virtual ~IEntityManager(){}
			
			//通过顶点和纹理图片创建实体
			virtual CEntity *CreateEntity(IVertex *pVertex, const char *texname = NULL) = 0;
		};
	}
}

#endif