#include "render/renderobject/CShadowMapObject.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CShadowMapObject::CShadowMapObject()
		{

		}

		CShadowMapObject::~CShadowMapObject()
		{

		}

		void CShadowMapObject::Create(IRenderable *pRenderable)
		{
			IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
			if (pShaderProgram)
			{
				pShaderProgram->Attach("shader/shadowrender.vs", ST_VERTEX);
				pShaderProgram->Attach("shader/shadowrender.ps", ST_FRAGMENT);
				pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				pShaderProgram->Link();

				float ambient[] = {.1f, .1f, .1f};
				float diffuse[] = { .8f, .8f, .6f };
				float specular[] = { .6f, .6f, .4f };
				pShaderProgram->SetUniform("material_ambient", ambient);
				pShaderProgram->SetUniform("material_diffuse", diffuse);
				pShaderProgram->SetUniform("material_specular", specular);
				float power = 128;
				pShaderProgram->SetUniform("material_specular_power", &power);

				
			}
		}

		void CShadowMapObject::SetTexture(IRenderable *pRenderable)
		{
			if (!pRenderable) return;
			IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
			if (pShaderProgram)
			{
				IShadowMap *pShadowMap = RENDERER->GetShadowMap();
				if (pShadowMap)
				{
					ITexture *pTex = pShadowMap->GetShadowMap();
					uint tex = 0;
					pShaderProgram->SetUniform("depth_texture", &tex);
					pRenderable->SetTexture(0, pTex);
				}
			}

		}

	}
}
