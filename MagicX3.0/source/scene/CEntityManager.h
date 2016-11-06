/************************************************************************/
/* ʵ�������                                                           */
/************************************************************************/

#ifndef _MX_SCENE_C_ENTITY_MANAGER_H_
#define _MX_SCENE_C_ENTITY_MANAGER_H_


#include "scene/IEntityManager.h"

namespace mx
{
	namespace scene
	{
		class CEntityManager : public IEntityManager
		{
		public:
			CEntityManager();
			virtual ~CEntityManager();

			virtual IEntity *CreateEntity(IVertex *pVertex);
			virtual IEntity *CreateEntity(IVertex *pVertex, const char *texname);
		};
	}
}

#endif