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
				IRenderPhase *pPhase = RENDERER->GetRenderPhaseManager()->GetRenderPhase((render::ERenderPhaseID)(phaseId));
				if (pPhase)
				{
					IRenderable *pRenderable = RENDERER->CreateRenderable(pPhase->GetRenderQueue(materialid));
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
							renderable->Bind();
							{
								UniformMap um;
								um["mvpMatrix"] = mvpMat4.m;
								um["mvMatrix"] = mvMat4.m;
								um["normalMatrix"] = normalMat3;
								um["mInverseMatrix"] = camInvMat4.m;

								UniformMap sum;
								CPointLight *pLight = (CPointLight *)pScene->GetLight(0);
								if (pLight)
								{
									CVector3 vLightPos = pLight->GetPosition();
									pCam->GetViewMatrix().TransformVect(vLightPos);
									um["vLightPos"] = vLightPos.v;

									ICamera *pLightCam = pScene->GetLightCamera(0);
									if (pLightCam)
									{
										CMatrix4 smvpMat4 = GetAbsluateTransformation() * pLightCam->GetViewProjectionMatrix();
										sum["mvpMatrix"] = smvpMat4.m;
									}
								}
								//renderable->SetTexture(m_pRenderable);

								for (auto it = um.begin(); it != um.end(); ++it)
								{
									renderable->SetUniform(it->first, it->second);
								}
							}

							renderable->SumbitToRenderQueue();

							renderable->UnBind();
						}

					}


				}
			}
		}

	}
}