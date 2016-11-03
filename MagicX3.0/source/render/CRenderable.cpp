#include "CRenderable.h"

namespace mx
{
	namespace render
	{

		CRenderable::CRenderable(IRenderList *pRenderList)
			:m_pRenderList(pRenderList)
			, m_bActive(true)
		{

		}

		CRenderable::~CRenderable()
		{

		}

		void CRenderable::SumbitToRenderQueue()
		{
			if (m_pRenderList)
				m_pRenderList->AddRenderable(this);
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


	}
}