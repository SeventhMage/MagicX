#ifndef _MX_SCENE_CMESHNODEMANAGER_H_
#define _MX_SCENE_CMESHNODEMANAGER_H_

#include <vector>

#include "render/IRenderer.h"
#include "render/IGPUBuffer.h"
#include "scene/CMeshNode.h"
#include "scene/IScene.h"
#include "resource/IMesh.h"

namespace mx
{
	namespace scene
	{
		using render::IRenderer;
		using render::IGPUBuffer;
		class CMeshNodeManager
		{
		public:
			CMeshNodeManager(IRenderer *pRenderer);
			~CMeshNodeManager();
			CMeshNode *CreateMeshNode(resource::IMesh *pMesh);
			void DestroyMeshNode(CMeshNode *pMeshNode);
		private:
			typedef std::vector<CMeshNode *> MeshTable;
			IRenderer *m_pRenderer;
			IGPUBuffer *m_pGPUBuffer;
			MeshTable m_tbMeshNode;
		};
	}
}

#endif