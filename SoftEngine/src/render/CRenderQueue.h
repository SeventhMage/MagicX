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
			CRenderQueue(IMaterial *pMaterial);
			virtual ~CRenderQueue();						
			virtual void AddRenderCell(IRenderCell *pCell);
			virtual IMaterial *GetMaterial() const { return m_pMaterial; }
			virtual void Clear();
			virtual void Render(scene::ICamera *pCamera);
		private:			
			int m_vaoId;			
			std::vector<IRenderCell *>m_RenderCellList;
			IMaterial *m_pMaterial;
		};
	}
}

#endif