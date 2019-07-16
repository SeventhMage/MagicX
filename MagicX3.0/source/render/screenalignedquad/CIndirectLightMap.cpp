#include "CIndirectLightMap.h"
#include "math/CVector3.h"
#include "math/CMatrix4.h"
#include "scene/IScene.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		static const int RAND_WIDTH = 16;
		using namespace mx::math;
		CIndirectLightMap::CIndirectLightMap(IRenderQueue *pRenderQueue)
			:CScreenAlignedQuad(pRenderQueue)
		{
			static const int RAND_NUM = RAND_WIDTH * RAND_WIDTH;
			byte vRandNum[RAND_NUM * 3] = { 0 };
			for (int i = 0; i < RAND_NUM; ++i)
			{
				float randRadius = 1.f * rand() / RAND_MAX;
				float randRadian = 1.f * rand() / RAND_MAX;
				float randRadian2 = 1.f * rand() / RAND_MAX;
				randRadian += randRadian2;
				vRandNum[3 * i] = (randRadius * sin(PI_2 * randRadian) * 127.f);
				vRandNum[3 * i + 1] = (randRadius * cos(PI_2 * randRadian) * 127.f);
			}

			m_pRandNumTex = RENDERER->CreateTexture(CF_RGB, RAND_WIDTH, RAND_WIDTH, CF_RGB, PT_UNSIGNED_BYTE, (void*)vRandNum);
			if (m_pRandNumTex)
			{
				int iTextureUnit = 0;
				m_pRenderable->SetTexture(iTextureUnit, m_pRandNumTex);
				m_pRenderable->GetShaderProgram()->SetUniform("tRandNum", &iTextureUnit);
			}
		}

		CIndirectLightMap::~CIndirectLightMap()
		{
			RENDERER->DestroyTexture(m_pRandNumTex);
			m_pRandNumTex = nullptr;
		}

		void CIndirectLightMap::Render()
		{
			CVector3 lightPos[MAX_LIGHT_NUM];
			CVector3 lightDir[MAX_LIGHT_NUM];
			CVector3 lightColor[MAX_LIGHT_NUM];
			CMatrix4 lightMatrix[MAX_LIGHT_NUM];
			CMatrix4 lightViewMatrix[MAX_LIGHT_NUM];
			CMatrix4 lightProjectMatrix[MAX_LIGHT_NUM];
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
			m_pRenderable->SetUniform("samplingColCount", &RAND_WIDTH);
			


			m_pRenderable->SumbitToRenderQueue();
		}

	}
}