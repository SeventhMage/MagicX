#include "CGuassianVBlur.h"
#include "mxDef.h"
#include "mx.h"
#include "device/IDevice.h"

namespace mx
{
	namespace render
	{

		CGuassianVBlur::CGuassianVBlur(IRenderQueue *pRenderQueue)
			:CScreenAlignedQuad(pRenderQueue)
		{
			float scale = 0.005f;
			float c = 0.f;
			//float seg = 0.1f;
			//float seg_2 = seg * seg;
			float ratio = 1.f * DEVICEMGR->GetDevice()->GetWindowWidth() / DEVICEMGR->GetDevice()->GetWindowHeight();
			for (auto d = 0; d < MAX_SAMPLER_COUNT; ++d)
			{
				float e = -1 + 2 * d / (MAX_SAMPLER_COUNT - 1.0f);
				float f = e;
				//f = expf(-0.5f * f * f / seg_2) / (2.f * PI * seg_2);
				f = expf(-0.5f * f * f /1.f) / 2.50662827463f;
				c += f;
				m_kernel[4 * d + 0] = 0;
				m_kernel[4 * d + 1] = e * scale * ratio;
				m_kernel[4 * d + 2] = f;
				m_kernel[4 * d + 3] = 0;
			}
			for (auto d = 0; d < MAX_SAMPLER_COUNT; ++d)
				m_kernel[4 * d + 2] /= c;
		}

		CGuassianVBlur::~CGuassianVBlur()
		{

		}

		void CGuassianVBlur::Render()
		{
			m_pRenderable->SetUniform("uKernel", m_kernel);
			m_pRenderable->SumbitToRenderQueue();
		}

	}
}