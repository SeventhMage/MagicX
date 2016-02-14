#ifndef _MX_SCENE_CMESHNODE_H_
#define _MX_SCENE_CMESHNODE_H_

#include <vector>

#include "ISceneNode.h"
#include "resource/IMesh.h"
#include "render/IGPUBuffer.h"
#include "render/IRenderableObject.h"

namespace mx
{
	namespace scene
	{
		using namespace render;
		class CMeshNode : public ISceneNode
		{
		public:
			CMeshNode(resource::IMesh *pMesh, render::IGPUBuffer *pBuffer);
			virtual ~CMeshNode();		

			virtual void UpdateImp(int elapsedTime);
			virtual void RenderImp();
		private:
			void CreatePLXRenderable(uint idx);
		private:
			resource::IMesh *m_pMesh;
			render::IGPUBuffer *m_pGPUBuffer;
			std::vector<render::IRenderableObject *> m_pRenderableObject;
		};
	}
}

#endif