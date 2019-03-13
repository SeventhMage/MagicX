#include "CShadowPlane.h"


CShadowPlane::CShadowPlane()
:m_pRenderable(nullptr)
{
	m_pRenderObject = new CShadowMapObject(RENDERER);
}

CShadowPlane::~CShadowPlane()
{
	SAFE_DEL(m_pRenderObject);
}

void CShadowPlane::UpdateImp(int delta)
{
	if (!m_pRenderable) return;

	IScene *pScene = SCENEMGR->GetCurrentScene();
	if (pScene)
	{
		m_pRenderable->Bind();

		ICamera *pCam = pScene->GetCamera();
		if (pCam)
		{
			CMatrix4 mvpMat4 = GetAbsluateTransformation() * pCam->GetViewProjectionMatrix();
			UniformMap um;
			um["model_matrix"] = (void *)GetAbsluateTransformation().m;
			um["view_matrix"] = (void *)pCam->GetViewMatrix().m;
			um["projection_matrix"] = (void *)pCam->GetProjectionMatrix().m;

			CMatrix4 scaleMat4(.5f, .0f, .0f, .0f, 
				.0f, .5f, .0f, .0f,
				.0f, .0f, .5f, .0f,
				.5f, .5f, .5f, 1.f);

			ILight *pLight = pScene->GetLight(0);
			CMatrix4 lightViewMat;
			CVector3 pos = ((CPointLight *)pLight)->GetPosition();

			ICamera *pLightCam = pScene->GetLightCamera(0);
			if (pLightCam)
			{
				CMatrix4 shadow_mat = pLightCam->GetViewProjectionMatrix() * scaleMat4;
				um["shadow_matrix"] = (void *)(shadow_mat.m);
			}

			CVector3 lightPos = pos;
			pCam->GetViewMatrix().TransformVect(lightPos);
			um["light_position"] = lightPos.v;			
			
			CMatrix4 temp = pCam->GetViewMatrix();
			temp.SetTranslation(CVector3(0, 0, 0));
			CVector3 normal(0, 1, 0);
			temp.TransformVect(normal);

			CVector3 vpos(-50, 0, 50);
			pCam->GetViewMatrix().TransformVect(vpos);
			CVector3 dir = lightPos - vpos;
			float dot = dir.dotProduct(normal);

			m_pRenderObject->Update(m_pRenderable, um);
		}

		m_pRenderable->SumbitToRenderList();

		m_pRenderable->UnBind();
	}
}

void CShadowPlane::Create()
{
	IVertexArrayObject *pVAO = m_pRenderObject->GetVAO();
	if (pVAO)
	{
		pVAO->Bind();
		m_pRenderable = RENDERER->CreateRenderable(pVAO->GetRenderList());

		m_pRenderObject->Create(m_pRenderable);

		float width = 50;
		float vertex[] = {-width, 0, width, 0, 1, 0,
			width, 0, width, 0, 1, 0,
			width, 0, -width, 0, 1, 0,
			
			
			-width, 0, width, 0, 1, 0,
			width, 0, -width, 0, 1, 0,
			-width, 0, -width, 0, 1, 0, };

		IBufferObject *bufferObject = m_pRenderable->CreateVertexBufferObject(vertex, sizeof(vertex), 0, sizeof(vertex) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

		pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 6 * sizeof(float), 0);
		pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 6 * sizeof(float), 3 * sizeof(float));

		m_pRenderable->Disable(RA_CULL_FACE);

		bufferObject->UnBind();
		pVAO->UnBind();

		m_pRenderObject->SetTexture(m_pRenderable);
		
	}
}
