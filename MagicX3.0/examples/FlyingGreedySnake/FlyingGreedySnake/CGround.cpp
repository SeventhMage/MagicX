#include "CGround.h"


CGround::CGround()
{
	m_pRenderObject = new CShadowMapObject();
}

CGround::~CGround()
{
	SAFE_DEL(m_pRenderObject);
}

void CGround::UpdateImp(int delta)
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
			lightViewMat.BuildCameraLookAtMatrix(pos, -pos, CVector3(0, 1, 0));
			CMatrix4 lightProMat;
			lightProMat.BuildProjectionMatrixPerspectiveFovRH(PI / 2.f, 1.f * 800 / 600, 1.f, 1000.f);

			CMatrix4 shadow_mat = lightViewMat * lightProMat * scaleMat4;
			CVector3 vTest(-50, 0, 50);
			float out[4];
			shadow_mat.TransformVect(out, vTest);
			um["shadow_matrix"] = (void *)((lightViewMat * lightProMat * scaleMat4).m);

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

void CGround::Create()
{
	IVertexArrayObject *pVAO = m_pRenderObject->GetVAO();
	if (pVAO)
	{
		pVAO->Bind();
		m_pRenderable = RENDERER->CreateRenderable(pVAO->GetRenderList());

		m_pRenderObject->Create(m_pRenderable);

		float width = 256;
		float vertex[] = { -width, 0, width, 0, 1, 0,
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

		ISceneNode *pRootNode = SCENEMGR->GetCurrentScene()->GetRootNode();
		pRootNode->AddChild(this);
	}
}