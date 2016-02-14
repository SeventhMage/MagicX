/*
*�����е�ʵ���࣬Ӣ�ۡ�NPC�������Ⱦ��ɼ̳д���
*/
#ifndef _MX_CENTITY_H_
#define _MX_CENTITY_H_

#include "scene/ISceneNode.h"
#include "resource/IMesh.h"
#include "render/IMaterial.h"

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
			std::string m_sMeshFile;
			resource::IMesh *m_pMeshData;
			render::IMaterial *m_pTexture;
		};
	}
}

#endif
