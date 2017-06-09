#include "CSoftRenderer.h"
#include "base/seDef.h"

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

	}
}