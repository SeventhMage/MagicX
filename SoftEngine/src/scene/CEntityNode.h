#ifndef _SCENE_C_ENTITY_NODE_H_
#define _SCENE_C_ENTITY_NODE_H_

#include "CSceneNode.h"

namespace se
{
	namespace scene
	{
		class CEntityNode : public CSceneNode
		{
		public:
			CEntityNode(const char *entityName, IScene *pScene);
			virtual ~CEntityNode();

			virtual void Update(int delta);

		public:
			IEntity *GetEntity(){ return m_pEntity; }

		private:
			IEntity *m_pEntity;						//场景中包含的实体
		};
	}
}

#endif