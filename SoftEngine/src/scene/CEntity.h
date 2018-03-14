#ifndef _SCENE_C_ENTITY_H_
#define _SCENE_C_ENTITY_H_

#include "scene/IEntity.h"
#include "render/IRenderCell.h"
#include "math/CVector3.h"
#include "math/CVector2.h"
#include "math/CAABBox.h"
#include "scene/IModel.h"

#include <string>
#include <vector>

namespace se
{
	namespace scene
	{		
		class CEntity : public IEntity
		{
		public:
			CEntity(const char *name, ISceneNode *pNode);
			virtual ~CEntity();

			virtual void Update(int delta);
        protected:
            void CalcBox(base::Vertices *pVertices);
		protected:
			std::string m_strEntityName;
            math::CAABBox m_aabbox;
			ISceneNode *m_pSceneNode;			//所属的场景结点
			render::IRenderCell *m_pRenderCell;
			IModel *m_pModel;
			uint m_bufferId;
		};
	}
}

#endif
