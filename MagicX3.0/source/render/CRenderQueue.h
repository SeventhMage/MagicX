#ifndef _MX_RENDER_C_RENDER_QUEUE_H_
#define _MX_RENDER_C_RENDER_QUEUE_H_

#include "render/IRenderQueue.h"

#include <vector>

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
			virtual void SetPhaseQuote(int phaseId);
			virtual void BindPhaseUniform();
		private:
			int m_materialId;
			std::vector<IRenderable *>m_vecRenderables;
			int m_phaseQuote;
		};
	}
}

#endif