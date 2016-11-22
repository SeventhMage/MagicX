#include "scene/renderobject/CShadowMapObject.h"

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

				float light[] = { .8f, .8f, .8f };
				pShaderProgram->SetUniform("material_ambient", light);
				pShaderProgram->SetUniform("material_diffuse", light);
				pShaderProgram->SetUniform("material_specular", light);
				float power = 30;
				pShaderProgram->SetUniform("material_specular_power", &power);

			}
		}

	}
}
