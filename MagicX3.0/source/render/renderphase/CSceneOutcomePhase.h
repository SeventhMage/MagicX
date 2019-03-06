#ifndef _MX_RENDER_C_SCENE_OUTCOME_PHASE_H_
#define _MX_RENDER_C_SCENE_OUTCOME_PHASE_H_

#include "CRenderPhase.h"
#include "render/renderobject/IRenderObject.h"
#include "render/IRenderable.h"

namespace mx
{
	namespace render
	{
		class CSceneOutcomePhase : public CRenderPhase
		{
		public:
			CSceneOutcomePhase(IRenderPhaseManager *pRenderPhaseMgr);
			~CSceneOutcomePhase();

			virtual void Initialize(IRenderer *pRenderer, int width, int height);
			virtual void Destroy();
			virtual int GetPhaseID() const { return ERPI_SCENEOUTCOME; }
			virtual void Render();
		private:
			IRenderable *m_pRenderable;
			IRenderObject *m_pRenderObject;
		};
	}
}

#endif