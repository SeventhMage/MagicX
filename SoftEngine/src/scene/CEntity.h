#ifndef _SCENE_C_ENTITY_H_
#define _SCENE_C_ENTITY_H_

#include "scene/IEntity.h"
#include "render/IRenderCell.h"
#include "math/CVector3.h"
#include "math/CVector2.h"
#include <string>
#include <vector>

namespace se
{
	namespace scene
	{
		class CSceneNode;
		class CEntity : public IEntity
		{
		public:
			CEntity(const char *name, CSceneNode *pNode);
			virtual ~CEntity();

			virtual void Update(int delta);
			virtual bool Culled(ICamera *pCamera);
		private:
			std::string m_strEntityName;
			CSceneNode *m_pSceneNode;			//所属的场景结点
			render::IRenderCell *m_pRenderCell;
		};
	}
}

#endif