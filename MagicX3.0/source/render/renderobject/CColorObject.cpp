#include "render/renderobject/CColorFlatObject.h"

namespace mx
{
	namespace render
	{

		CColorFlatObject::CColorFlatObject(IRenderer *pRenderer, float fColor[4])
			:CRenderObject(pRenderer)
		{
			memcpy(m_fColor, fColor, 4 * sizeof(float));
			if (m_pShaderProgram)
			{
				m_pShaderProgram->CreateStandShader(ESS_SHADER_FLAT);
				m_pShaderProgram->SetUniform("vColor", m_fColor);
			}
		}

		CColorFlatObject::~CColorFlatObject()
		{

		}

		void CColorFlatObject::Create(IRenderable *pRenderable)
		{			
			if (m_pShaderProgram)
			{			
				pRenderable->SetShaderProgram(m_pShaderProgram);
			}
		}

	}
}