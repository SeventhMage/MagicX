/*
*场景中的实体类，英雄、NPC、建筑等均可继承此类
*/
#ifndef _MX_CENTITY_H_
#define _MX_CENTITY_H_

#include "ISceneNode.h"
#include "IMesh.h"
#include "../include/IMaterial.h"

namespace mx
{
	namespace scene
	{
		class CEntity : public ISceneNode
		{
		public:
			CEntity();
			virtual ~CEntity();
			
			bool LoadEntity(const char *filename);

		private:
			CString m_sMeshFile;
			IMesh *m_pMeshData;
			render::IMaterial *m_pTexture;
		};
	}
}

#endif
