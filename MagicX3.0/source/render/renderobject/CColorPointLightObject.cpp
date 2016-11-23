#include "render/renderobject/CColorPointLightObject.h"

namespace mx
{
	namespace render
	{
		CColorPointLightObject::CColorPointLightObject(float fColor[4])
		{
			memcpy(m_fColor, fColor, 4 * sizeof(float));
		}

		CColorPointLightObject::~CColorPointLightObject()
		{

		}

		void CColorPointLightObject::Create(IRenderable *pRenderable)
		{
			IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
			if (pShaderProgram)
			{
				pShaderProgram->CreateStandShader(ESS_SHADER_POINT_LIGHT_DIFF);
				pShaderProgram->SetUniform("vColor", m_fColor);
			}
		}

	}
}