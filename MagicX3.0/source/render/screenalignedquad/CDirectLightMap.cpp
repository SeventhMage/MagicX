#include "CDirectLightMap.h"
#include "math/CVector3.h"
#include "math/CMatrix4.h"
#include "scene/IScene.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		using namespace mx::math;
		CDirectLightMap::CDirectLightMap(IRenderQueue *pRenderQueue)
			:CScreenAlignedQuad(pRenderQueue)
		{

		}

		CDirectLightMap::~CDirectLightMap()
		{

		}

		void CDirectLightMap::Render()
		{
			CVector3 lightPos[MAX_LIGHT_NUM];
			CVector3 lightDir[MAX_LIGHT_NUM];
			CVector3 lightColor[MAX_LIGHT_NUM];
			CMatrix4 lightMatrix[MAX_LIGHT_NUM];
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

					ICamera *pLightCam = SCENEMGR->GetCurrentScene()->GetLightCamera(i);
					if (pLightCam)
					{
						lightMatrix[i] = pLightCam->GetViewProjectionMatrix() * scaleMat4;
					
					}

					memcpy(lightColor[i].v, pLight->GetColor(), sizeof(lightColor[i].v));
				}
			}

			m_pRenderable->SetUniform("shadowMatrix", lightMatrix);
			m_pRenderable->SetUniform("lightPosition", lightPos);
			m_pRenderable->SetUniform("lightDir", lightDir);
			m_pRenderable->SetUniform("lightColor", lightColor);


			m_pRenderable->SumbitToRenderQueue();
		}
	}
}