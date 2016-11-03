#include "CRenderable.h"

namespace mx
{
	namespace render
	{

		CRenderable::CRenderable()
		{

		}

		CRenderable::~CRenderable()
		{

		}

		void CRenderable::SumbitToRenderQueue()
		{
			if (m_pRenderQueue)
				m_pRenderQueue->AddRenderable(this);
		}

		void CRenderable::Bind()
		{
			if (m_pShaderProgram)
				m_pShaderProgram->Bind();
			if (m_pVBO)
				m_pVBO->Bind();
			if (m_pIBO)
				m_pIBO->Bind();
			
			for (int i = 0; i < TU_TEXTURE_NUM; ++i)
			{
				if (m_pTexture[i])
					m_pTexture[i]->Bind(i);
			}
		}

		void CRenderable::Render()
		{

		}


	}
}