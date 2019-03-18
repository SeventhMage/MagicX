#include "scene/CScreenAlignedQuad.h"
#include "mx.h"

#include <time.h>

namespace mx
{
	namespace scene
	{
		CScreenAlignedQuad::CScreenAlignedQuad(int phaseid, int materialid)
		{
			float vertex[] = { -1, -1, 0, 0, 0,
				1, -1, 0, 1, 0,
				1, 1, 0, 1, 1,
				-1, -1, 0, 0, 0,
				1, 1, 0, 1, 1,
				-1, 1, 0, 0, 1 };

			//for (int i = 0; i < sizeof(vertex) / sizeof(float); ++i)
			//{
			//	vertex[i] *= 0.2f;
			//	vertex[i] -= 0.5f;
			//}

			IRenderPhase *pPhase = RENDERER->GetRenderPhaseManager()->GetRenderPhase((phaseid));
			if (pPhase)
			{
				IRenderQueue *pRenderQueue = pPhase->GetRenderQueue(materialid);
				m_pRenderable = RENDERER->CreateRenderable(pPhase->GetRenderQueue(materialid));
				IMaterial *pMaterial = RENDERER->GetMaterialManager()->GetMaterial(materialid);
				if (pMaterial)
				{
					m_pRenderable->SetShaderProgram(pMaterial->GetShaderProgram());
				}
				CMatrix4 scaleMat4(.5f, .0f, .0f, .0f,
					.0f, .5f, .0f, .0f,
					.0f, .0f, .5f, .0f,
					.5f, .5f, .5f, 1.f);
				CVector3 lightPos[64];
				CVector3 lightColor[64];
				CMatrix4 lightMatrix[64];
				srand(time(0));
				for (int i = 0; i < 64; ++i)
				{
					lightPos[i].set(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50);
					lightColor[i].set(1.f * (rand() % 256) / 25600, 1.f * (rand() % 256) / 25600, 1.f * (rand() % 256) / 25600);

					CPointLight *pLight = (CPointLight *) SCENEMGR->GetCurrentScene()->SetupLight(i, LT_POINT, lightColor[i].v);
					pLight->SetPosition(lightPos[i]);
					ICamera *pCam = SCENEMGR->GetCurrentScene()->SetupLightCamera(0, lightPos[i], -lightPos[i], CVector3(0, 1, 0), PI * 0.5f, 1.f, 1.f, 1000.f);
					lightMatrix[i] = pCam->GetViewProjectionMatrix() * scaleMat4;
				}

				m_pRenderable->SetUniform("shadowMatrix", lightMatrix);
				m_pRenderable->SetUniform("lightPosition", lightPos);
				m_pRenderable->SetUniform("lightColor", lightColor);

				IVertexArrayObject *pVAO = m_pRenderable->GetVertexArrayObject();
				pVAO->Bind();
				IBufferObject *bufferObject = m_pRenderable->CreateVertexBufferObject(vertex, sizeof(vertex), 0, sizeof(vertex) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);


				pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 5 * sizeof(float), 0);
				pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, 5 * sizeof(float), 3 * sizeof(float));


				bufferObject->UnBind();
				pVAO->UnBind();
			}
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