#ifndef _MX_RENDER_C_RENDER_QUEUE_H_
#define _MX_RENDER_C_RENDER_QUEUE_H_

#include "render/IRenderQueue.h"

#include <vector>

#include "SUniform.h"

namespace mx
{
	namespace render
	{
		class CRenderQueue : public IRenderQueue
		{
		public:
			CRenderQueue(int materiadId);
			~CRenderQueue();
			virtual void AddRenderable(IRenderable *renderable);
			virtual void Clear();
			virtual void Render();
			virtual IMaterial *GetMaterial() const;
			virtual void BindPhaseUniform();
			virtual void SetPhaseTexture(const char *name, int phaseid, int slot, int index);
		private:
			int m_materialId;
			std::vector<IRenderable *>m_vecRenderables;
			struct PhaseTexture 
			{
				std::string name;
				int phaseid;
				int index;
				ITexture *texture;
			};
			std::map<int, PhaseTexture> m_mapSlotTexture;
		};
	}
}

#endif