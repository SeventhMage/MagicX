#include "CIndirectLightMap.h"
#include "math/CVector3.h"
#include "math/CMatrix4.h"
#include "scene/IScene.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		using namespace mx::math;
		CIndirectLightMap::CIndirectLightMap(IRenderQueue *pRenderQueue)
			:CScreenAlignedQuad(pRenderQueue)
		{

		}

		CIndirectLightMap::~CIndirectLightMap()
		{

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

			static const int RAND_NUM = 256;
			static float fSRandNum[RAND_NUM] = { 0 };
			static float fCRandNum[RAND_NUM] = { 0 };
			for (int i = 0; i < RAND_NUM; ++i)
			{
				if (fSRandNum[i] > 0)
					break;
				float randRadius = 1.f * rand() / RAND_MAX;
				float randRadian = 1.f * rand() / RAND_MAX;
				float randRadian2 = 1.f * rand() / RAND_MAX;
				randRadian += randRadian2;
				fSRandNum[i] = randRadius * sin(PI_2 * randRadian);
				fCRandNum[i] = randRadius * cos(PI_2 * randRadian);
			}
			m_pRenderable->SetUniform("fSRandNum", fSRandNum);
			m_pRenderable->SetUniform("fCRandNum", fCRandNum);

			m_pRenderable->SumbitToRenderQueue();
		}

	}
}