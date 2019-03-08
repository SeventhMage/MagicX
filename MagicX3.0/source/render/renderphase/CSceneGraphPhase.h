#ifndef _MX_RENDER_C_SCENE_GRAPH_PHASE_H_
#define _MX_RENDER_C_SCENE_GRAPH_PHASE_H_

#include "CRenderPhase.h"
namespace mx
{
	namespace render
	{
		class CSceneGraphPhase : public CRenderPhase
		{
		public:
			CSceneGraphPhase(IRenderPhaseManager *pRenderPhaseMgr);
			~CSceneGraphPhase();

			virtual void Initialize(IRenderer *pRenderer, int width, int height);
			virtual void Destroy();
			virtual void Render();
			virtual int GetPhaseID() const { return ERPI_SCENEGRAPH; }
		};
	}
}

#endif
