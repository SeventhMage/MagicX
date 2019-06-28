#include "CGround.h"


CGround::CGround()
{
	AddRenderPhase(1, 1);
	AddRenderPhase(3, 3);
}

CGround::~CGround()
{
}

void CGround::UpdateImp(int delta)
{
	CEntity::UpdateImp(delta);
}

void CGround::Create(float width)
{
	for (auto renderable : m_vecRenderables)
	{
		IVertexArrayObject *pVAO = renderable->GetVertexArrayObject();
		if (pVAO)
		{
			pVAO->Bind();
			ITexture *pTexture = RENDERER->CreateTexture("texture/floor.tga");
			renderable->SetTexture(0, pTexture);

			float vertex[] = { -width, 0, width, 0, 1, 0, 0, 0,
				width, 0, width, 0, 1, 0, 20, 0,
				width, 0, -width, 0, 1, 0, 20, 20,


				-width, 0, width, 0, 1, 0, 0, 0,
				width, 0, -width, 0, 1, 0, 20, 20,
				-width, 0, -width, 0, 1, 0, 0, 20};

			IBufferObject *bufferObject = renderable->CreateVertexBufferObject(vertex, sizeof(vertex), 0, sizeof(vertex) / sizeof(float), GBM_TRIANGLES, GBU_DYNAMIC_DRAW);

			pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 8 * sizeof(float), 0);
			pVAO->EnableVertexAttrib(render::VAL_NORMAL, 3, render::RVT_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
			pVAO->EnableVertexAttrib(render::VAL_TEXTURE0, 2, render::RVT_FLOAT, 8 * sizeof(float), 6 * sizeof(float));

			renderable->Disable(RA_CULL_FACE);

			bufferObject->UnBind();
			pVAO->UnBind();

			renderable->SetUniform("color", CVector3(.8f, .8f, .8f).v);
			ISceneNode *pRootNode = SCENEMGR->GetCurrentScene()->GetRootNode();
			pRootNode->AddChild(this);
		}
	}

}
