#include "CScreenAlignedQuad.h"
#include "mx.h"

#include <time.h>

namespace mx
{
	namespace render
	{
		CScreenAlignedQuad::CScreenAlignedQuad(IRenderQueue *pRenderQueue)
			:m_pRenderable(nullptr)
		{
			float vertex[] = { -1, -1, 0, 0, 0,
				1, -1, 0, 1, 0,
				1, 1, 0, 1, 1,
				-1, -1, 0, 0, 0,
				1, 1, 0, 1, 1,
				-1, 1, 0, 0, 1 };
			m_pRenderable = RENDERER->CreateRenderable(pRenderQueue);
			IMaterial *pMaterial = pRenderQueue->GetMaterial();
			if (pMaterial)
			{
				m_pRenderable->SetShaderProgram(pMaterial->GetShaderProgram());
			}


			IVertexArrayObject *pVAO = m_pRenderable->GetVertexArrayObject();
			pVAO->Bind();
			IBufferObject *bufferObject = m_pRenderable->CreateVertexBufferObject(vertex, sizeof(vertex), 0, 6, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);


			pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 5 * sizeof(float), 0);
			pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, 5 * sizeof(float), 3 * sizeof(float));


			bufferObject->UnBind();
			pVAO->UnBind();
		}

		CScreenAlignedQuad::~CScreenAlignedQuad()
		{
			RENDERER->DestroyRenderable(m_pRenderable);
		}

		void CScreenAlignedQuad::Render()
		{
			if (m_pRenderable)
				m_pRenderable->SumbitToRenderQueue();
		}

	}
}