/************************************************************************/
/* 场景中的一个实体                                                     */
/************************************************************************/

#ifndef _MX_SCENE_C_ENTITY_H_
#define _MX_SCENE_C_ENTITY_H_

#include "CSceneNode.h"
#include "render/IRenderable.h"

#include <vector>
#include <map>

namespace mx
{
	namespace scene
	{
		class CEntity : public CSceneNode
		{
		public:
			CEntity();
			virtual ~CEntity();
			void AddRenderPhase(int phaseId, int materialid);
			void SetGlobalUniform();
		protected:
			typedef std::vector<int> RENDER_QUEUE;
			typedef std::map<int, RENDER_QUEUE> PHASE_MAP;
			PHASE_MAP m_PhaseQueue;
			std::vector<render::IRenderable *> m_vecRenderables;
		};
	}
}

#endif