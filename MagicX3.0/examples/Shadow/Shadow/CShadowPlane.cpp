#include "CShadowPlane.h"


CShadowPlane::CShadowPlane()
:m_pRenderable(nullptr)
{
	m_pRenderObject = new CShadowMapObject();
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

			CMatrix4 lightView;
			ILight *pLight = pScene->GetLight(0);
			CMatrix4 lightViewMat;
			CVector3 pos = ((CPointLight *)pLight)->GetPosition();
			lightViewMat.BuildCameraLookAtMatrix(pos, -pos, CVector3(0, 1, 0));
			CMatrix4 lightProMat;
			lightProMat.BuildProjectionMatrixPerspectiveFovRH(PI / 3.f, 1.f * 800 / 600, 1.f, 1000.f);

			um["shadow_matrix"] = (void *)((lightView * lightProMat * scaleMat4).m);

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

		bufferObject->UnBind();
		pVAO->UnBind();
		
	}
}
