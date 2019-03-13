#include "render/renderobject/CColorPointLightObject.h"

namespace mx
{
	namespace render
	{
		CColorPointLightObject::CColorPointLightObject(IRenderer *pRenderer, float fColor[4])
			:CRenderObject(pRenderer)
		{
			memcpy(m_fColor, fColor, 4 * sizeof(float));
			if (m_pShaderProgram)
			{
				m_pShaderProgram->CreateStandShader(ESS_SHADER_POINT_LIGHT_DIFF);
				m_pShaderProgram->SetUniform("vColor", m_fColor);
			}
		}

		CColorPointLightObject::~CColorPointLightObject()
		{

		}

		void CColorPointLightObject::Create(IRenderable *pRenderable)
		{
			if (m_pShaderProgram)
			{
				pRenderable->SetShaderProgram(m_pShaderProgram);
				m_pShaderProgram->SetUniform("vColor", m_fColor);
			}
		}

	}
}