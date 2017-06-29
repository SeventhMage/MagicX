#ifndef _RENDER_C_RENDER_QUEUE_H_
#define _RENDER_C_RENDER_QUEUE_H_

#include "render/IRenderQueue.h"
#include "render/IMaterial.h"

#include <vector>

namespace se
{
	namespace render
	{
		class CRenderQueue : public IRenderQueue
		{
		public:
			CRenderQueue(const char *material);
			virtual ~CRenderQueue();
			virtual int GetMaterialID(){ return m_materialId; }
			virtual void AddRenderCell(IRenderCell *pCell);
			virtual void Clear();
			virtual void Render();
		private:
			int m_materialId;
			std::vector<IRenderCell *>m_RenderCellList;
		};
	}
}

#endif