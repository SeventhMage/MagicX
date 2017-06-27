#include "CRenderQueue.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{

		CRenderQueue::CRenderQueue(const char *material)
		{
			m_materialId = CSoftEngine::GetMaterialManager()->CreateMaterial(material);
		}

		CRenderQueue::~CRenderQueue()
		{
			CSoftEngine::GetMaterialManager()->DestroyMaterial(m_materialId);
		}

	}
}