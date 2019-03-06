#include "CSceneOutcomePhase.h"
#include "mx.h"
#include "render/renderobject/CTextureMapObject.h"

namespace mx
{
	namespace render
	{
		CSceneOutcomePhase::CSceneOutcomePhase(IRenderPhaseManager *pPhaseMgr)
			:CRenderPhase(ERTF_DEFAULT, pPhaseMgr), m_pRenderable(nullptr), m_pRenderObject(nullptr)
		{
		}
		CSceneOutcomePhase::~CSceneOutcomePhase()
		{
		}

		void CSceneOutcomePhase::Initialize(IRenderer *pRenderer, int width, int height)
		{
			m_pRenderTarget = pRenderer->GetRenderTargetManager()->CreateRenderTarget(m_renderTargetFlag, width, height);

			m_pRenderObject = new CTextureMapObject(pRenderer);
			IVertexArrayObject *pVAO = m_pRenderObject->GetVAO();
			if (pVAO)
			{
				pVAO->Bind();
				m_pRenderable = pRenderer->CreateRenderable(pVAO->GetRenderList());

				m_pRenderObject->Create(m_pRenderable);

				float vertex[] = {-1, -1, 0, 0, 0,
					1, -1, 0, 1, 0,
					1, 1, 0, 1, 1,
					-1, -1, 0, 0, 0,
					1, 1, 0, 1, 1,
					-1, 1, 0, 0, 1 };

				IBufferObject *bufferObject = m_pRenderable->CreateVertexBufferObject(vertex, sizeof(vertex), 0, sizeof(vertex) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

				pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 6 * sizeof(float), 0);
				pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

				bufferObject->UnBind();
				pVAO->UnBind();

			}
		}

		void CSceneOutcomePhase::Destroy()
		{
			SAFE_DEL(m_pRenderTarget);
		}

		void CSceneOutcomePhase::Render()
		{
			if (!IsEnable()) return;
			if (m_pRenderTarget)
			{
				m_pRenderTarget->BeginTarget();
				IRenderPhase *pRenderPhase = m_pRenderPhaseManager->GetRenderPhase(ERPI_SCENEGRAPH);
				if (pRenderPhase)
				{
					IRenderTarget *pRenderTarget = pRenderPhase->GetRenderTarget();
					if (pRenderTarget)
					{
						m_pRenderable->SetTexture(0, pRenderTarget->GetBindTexture());
					}
				}
				IVertexArrayObject *pVAO = m_pRenderObject->GetVAO();
				if (pVAO)
				{
					m_pRenderable->SumbitToRenderList();
					pVAO->Render();
					pVAO->EndRender();
				}
				m_pRenderTarget->EndTarget();
			}
		}
	}
}