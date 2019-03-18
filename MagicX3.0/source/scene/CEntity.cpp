#include "scene/CEntity.h"
#include "render/IRenderQueue.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{

		CEntity::CEntity()
		{

		}

		CEntity::~CEntity()
		{
			for (auto renderable : m_vecRenderables)
			{
				SAFE_DEL(renderable);
			}
		}

		void CEntity::AddRenderPhase(int phaseId, int materialid)
		{
			if (std::find(m_PhaseQueue[phaseId].begin(), m_PhaseQueue[phaseId].end(), materialid) == m_PhaseQueue[phaseId].end())
			{
				m_PhaseQueue[phaseId].push_back(materialid);
				IRenderPhase *pPhase = RENDERER->GetRenderPhaseManager()->GetRenderPhase(phaseId);
				if (pPhase)
				{
					IRenderQueue *pRenderQueue = pPhase->GetRenderQueue(materialid);
					assert(pRenderQueue);
					IRenderable *pRenderable = RENDERER->CreateRenderable(pRenderQueue);
					IMaterial *pMaterial = RENDERER->GetMaterialManager()->GetMaterial(materialid);
					if (pMaterial)
					{
						pRenderable->SetShaderProgram(pMaterial->GetShaderProgram());
					}
					m_vecRenderables.push_back(pRenderable);
				}
			}
		}

		void CEntity::UpdateImp(int delta)
		{
			IScene *pScene = SCENEMGR->GetCurrentScene();
			if (pScene)
			{
				ICamera *pCam = pScene->GetCamera();
				if (pCam)
				{
					//const CFrustum &frustum = pCam->GetFrustum();
					//if (frustum.CullSphere(GetPosition(), m_fRadius))//²Ã¼ôµôÁË
					//	return;

					CMatrix4 mvpMat4 = GetAbsluateTransformation() * pCam->GetViewProjectionMatrix();
					CMatrix4 mvMat4 = GetAbsluateTransformation() * pCam->GetViewMatrix();
					CMatrix4 mvRotMat4 = mvMat4;
					mvRotMat4.SetTranslation(CVector3(0, 0, 0));
					CMatrix4 normalMat4;
					CMatrix4 camInvMat4;
					mvRotMat4.GetInverse(camInvMat4);
					camInvMat4.GetTransposed(normalMat4);

					pCam->GetViewMatrix().GetInverse(camInvMat4);
					camInvMat4.SetTranslation(CVector3(0, 0, 0));
					ISkyBox *pSkyBox = pScene->GetSkyBox();
					if (pSkyBox)
					{
						CMatrix4 skyBoxMat4 = pSkyBox->GetModelMatrix();
						CMatrix4 skyBoxInvMat4;
						skyBoxMat4.GetInverse(skyBoxInvMat4);

						camInvMat4 = skyBoxInvMat4 * camInvMat4;
					}


					float normalMat3[] = { normalMat4.m[0], normalMat4.m[1], normalMat4.m[2],
						normalMat4.m[4], normalMat4.m[5], normalMat4.m[6],
						normalMat4.m[8], normalMat4.m[9], normalMat4.m[10] };




					for (auto renderable : m_vecRenderables)
					{
						if (renderable)
						{
							renderable->SetUniform("viewMatrix", pCam->GetViewMatrix().m);
							renderable->SetUniform("projMatrix", pCam->GetProjectionMatrix().m);
							renderable->SetUniform("modelMatrix", GetAbsluateTransformation().m);
							renderable->SetUniform("normalMatrix", normalMat3);
							renderable->SetUniform("mInverseMatrix", camInvMat4.m);

							for (int i = 0; i < MAX_LIGHT_NUM; ++i)
							{
								ICamera *pLightCam = pScene->GetLightCamera(i);
								if (pLightCam)
								{
									renderable->SetUniform("viewLightMatrix", pLightCam->GetViewMatrix().m);
									renderable->SetUniform("projLightMatrix", pLightCam->GetProjectionMatrix().m);
								}
							}

							renderable->SumbitToRenderQueue();
						}

					}


				}
			}
		}

	}
}