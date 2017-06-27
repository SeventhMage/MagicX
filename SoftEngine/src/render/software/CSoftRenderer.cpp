#include "CSoftRenderer.h"
#include "base/seDef.h"
#include "../CRenderQueue.h"

namespace se
{
	namespace render
	{
		CSoftRenderer::CSoftRenderer()
			:m_pSoftRD(new CSoftRenderDriver())
		{

		}

		CSoftRenderer::~CSoftRenderer()
		{
			SAFE_DEL(m_pSoftRD);
		}

		IRenderQueue * CSoftRenderer::CreateRenderQueue(const char *material)
		{
			return new CRenderQueue(material);
		}

		void CSoftRenderer::DestroyRenderQueue(IRenderQueue *pRenderQueue)
		{
			SAFE_DEL(pRenderQueue);
		}

	}
}