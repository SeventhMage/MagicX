/************************************************************************/
/* ʵ��������ӿ�                                                       */
/************************************************************************/

#ifndef _MX_I_SCENE_I_ENTITY_MANAGER_H_
#define _MX_I_SCENE_I_ENTITY_MANAGER_H_

#include "IEntity.h"
#include "IVertex.h"

namespace mx
{
	namespace scene
	{
		class IEntityManager
		{
		public:
			virtual ~IEntityManager();

			//ͨ�����㴴��
			virtual IEntity *CreateEntity(IVertex *pVertex);
			
			//ͨ�����������ͼƬ����ʵ��
			virtual IEntity *CreateEntity(IVertex *pVertex, const char *texname);
		};
	}
}

#endif