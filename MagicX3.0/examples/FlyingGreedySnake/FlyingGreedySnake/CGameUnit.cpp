#include "CGameUnit.h"

CGameUnit::CGameUnit()
:m_pRenderable(nullptr)
, m_pRenderObject(nullptr)
, m_bAlive(true)
{

}

CGameUnit::~CGameUnit()
{

}

void CGameUnit::UpdateImp(int delta)
{
	if (!m_bAlive)
	{
		delete this;
		return;
	}


	IScene *pScene = SCENEMGR->GetCurrentScene();
	if (pScene)
	{
		ICamera *pCam = pScene->GetCamera();
		if (pCam)
		{
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

			if (m_pRenderable)
			{
				m_pRenderable->Bind();
				if (m_pRenderObject)
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

						CMatrix4 lightViewMat;
						CVector3 pos = ((CPointLight *)pLight)->GetPosition();
						lightViewMat.BuildCameraLookAtMatrix(pos, -pos, CVector3(0, 1, 0));
						CMatrix4 lightProMat;
						lightProMat.BuildProjectionMatrixPerspectiveFovRH(PI / 2.f, 1.f * 800 / 600, 1.f, 1000.f);
						CMatrix4 smvpMat4 = GetAbsluateTransformation() * lightViewMat * lightProMat;



						sum["mvpMatrix"] = smvpMat4.m;

					}

					m_pRenderObject->Update(m_pRenderable, um, &sum);
				}
				m_pRenderable->SumbitToRenderList();

				m_pRenderable->UnBind();
			}

		}
	}
}

