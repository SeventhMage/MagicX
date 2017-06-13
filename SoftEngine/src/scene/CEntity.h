#ifndef _SCENE_C_ENTITY_H_
#define _SCENE_C_ENTITY_H_

#include "scene/IEntity.h"
#include "resource/IModel.h"
#include "math/CVector3.h"
#include "math/CVector2.h"
#include <string>
#include <vector>

namespace se
{
	namespace scene
	{
		//面索引
		struct SFaceIndex
		{
			int position;
			int texcoord;
			int normal;
		};

		struct SPolygon
		{
			std::vector<math::CVector3> positionList;
			std::vector<math::CVector3> normalList;
			std::vector<math::CVector2> texCoordList;
			std::vector<SFaceIndex> faceList;
		};

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
			resource::IModel *m_pModel;			
		};
	}
}

#endif