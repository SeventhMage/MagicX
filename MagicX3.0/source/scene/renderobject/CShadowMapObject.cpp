#include "scene/renderobject/CShadowMapObject.h"
#include "mx.h"

namespace mx
{
	namespace scene
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
				float light[] = { .8f, .8f, .8f };
				//pShaderProgram->SetUniform("material_ambient", ambient);
				//pShaderProgram->SetUniform("material_diffuse", light);
				//pShaderProgram->SetUniform("material_specular", light);
				float power = 30;
				pShaderProgram->SetUniform("material_specular_power", &power);

				IShadowMap *pShadowMap = RENDERER->GetShadowMap();
				if (pShadowMap)
				{
					uint tex = pShadowMap->GetShadowMap();
					pShaderProgram->SetUniform("depth_texture", &tex);
				}
			}
		}

	}
}
