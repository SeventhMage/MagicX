#include "render/renderobject/CShadowMapObject.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CShadowMapObject::CShadowMapObject(IRenderer *pRenderer)
			:CRenderObject(pRenderer)
		{
			if (m_pShaderProgram)
			{
				m_pShaderProgram->Attach("shader/shadowrender.vs", ST_VERTEX);
				m_pShaderProgram->Attach("shader/shadowrender.ps", ST_FRAGMENT);
				m_pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				m_pShaderProgram->Link();

				float ambient[] = { .1f, .1f, .1f };
				float diffuse[] = { .8f, .8f, .6f };
				float specular[] = { .6f, .6f, .4f };
				m_pShaderProgram->SetUniform("material_ambient", ambient);
				m_pShaderProgram->SetUniform("material_diffuse", diffuse);
				m_pShaderProgram->SetUniform("material_specular", specular);
				float power = 128;
				m_pShaderProgram->SetUniform("material_specular_power", &power);


			}
		}

		CShadowMapObject::~CShadowMapObject()
		{

		}

		void CShadowMapObject::Create(IRenderable *pRenderable)
		{
			if (m_pShaderProgram)
			{
				pRenderable->SetShaderProgram(m_pShaderProgram);
			}
		}

		void CShadowMapObject::SetTexture(IRenderable *pRenderable)
		{
			if (!pRenderable) return;
			IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
			if (pShaderProgram)
			{
				ITexture *pTex = MagicX->GetRenderPhaseManager()->GetRenderPhase(ERPI_SHADOWMAP)->GetRenderTarget()->GetDepthTexture();
				uint tex = 0;
				pShaderProgram->SetUniform("depth_texture", &tex);
				pRenderable->SetTexture(0, pTex);
			}

		}

	}
}
