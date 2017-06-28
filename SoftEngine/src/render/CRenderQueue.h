#ifndef _RENDER_C_RENDER_QUEUE_H_
#define _RENDER_C_RENDER_QUEUE_H_

#include "render/IRenderQueue.h"
#include "render/IMaterial.h"

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
		private:
			int m_materialId;
		};
	}
}

#endif