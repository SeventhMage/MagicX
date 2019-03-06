#include "render/renderobject/CColorPointLightObject.h"

namespace mx
{
	namespace render
	{
		CColorPointLightObject::CColorPointLightObject(IRenderer *pRenderer, float fColor[4])
			:CRenderObject(pRenderer)
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