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


				IVertexArrayObject *pVAO = m_pRenderable->GetVertexArrayObject();
				pVAO->Bind();
				IBufferObject *bufferObject = m_pRenderable->CreateVertexBufferObject(vertex, sizeof(vertex), 0, 6, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);


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
			CVector3 lightPos[64];
			CVector3 lightDir[64];
			CVector3 lightColor[64];
			CMatrix4 lightMatrix[64];
			CMatrix4 lightViewMatrix[64];
			CMatrix4 lightProjectMatrix[64];
			CMatrix4 scaleMat4(.5f, .0f, .0f, .0f,
				.0f, .5f, .0f, .0f,
				.0f, .0f, .5f, .0f,
				.5f, .5f, .5f, 1.f);

			for (int i = 0; i < MAX_LIGHT_NUM; ++i)
			{
				ILight *pLight = SCENEMGR->GetCurrentScene()->GetLight(i);
				if (pLight)
				{
					switch (pLight->GetLightType())
					{
					case LT_DIRECTIONAL:
					{
						CDirectionalLight *pPointLight = (CDirectionalLight*)pLight;
						lightDir[i] = pPointLight->GetDirection();
					}
					break;
					case LT_POINT:
					{
						CPointLight *pPointLight = (CPointLight*)pLight;
						lightPos[i] = pPointLight->GetPosition();
					}
					break;
					}

					memcpy(lightColor[i].v, pLight->GetColor(), sizeof(lightColor[i].v));
				}

				ICamera *pLightCam = SCENEMGR->GetCurrentScene()->GetLightCamera(i);
				if (pLightCam)
				{
					lightMatrix[i] = pLightCam->GetViewProjectionMatrix() * scaleMat4;
					lightViewMatrix[i] = pLightCam->GetViewMatrix();
					lightProjectMatrix[i] = pLightCam->GetProjectionMatrix();
				}
			}

			m_pRenderable->SetUniform("shadowMatrix", lightMatrix);
			m_pRenderable->SetUniform("lightViewMatrix", lightViewMatrix);
			m_pRenderable->SetUniform("lightProjectMatrix", lightProjectMatrix);
			m_pRenderable->SetUniform("scaleMatrix", scaleMat4.m);
			m_pRenderable->SetUniform("lightPosition", lightPos);
			m_pRenderable->SetUniform("lightDir", lightDir);
			m_pRenderable->SetUniform("lightColor", lightColor);

			static const int RAND_NUM = 256;
			static float fSRandNum[RAND_NUM] = { 0 };
			static float fCRandNum[RAND_NUM] = { 0 };
			for (int i = 0; i < RAND_NUM; ++i)
			{
				if (fSRandNum[i] > 0)
					break;
				float randRadius = 1.f * rand() / RAND_MAX;
				float randRadian = 1.f * rand() / RAND_MAX;
				fSRandNum[i] = randRadius * sin(PI_2 * randRadian);
				fCRandNum[i] = randRadius * cos(PI_2 * randRadian);
			}
			m_pRenderable->SetUniform("fSRandNum", fSRandNum);
			m_pRenderable->SetUniform("fCRandNum", fCRandNum);

			if (m_pRenderable)
				m_pRenderable->SumbitToRenderQueue();
		}

	}
}