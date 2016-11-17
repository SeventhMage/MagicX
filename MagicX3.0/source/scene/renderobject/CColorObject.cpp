#include "scene/renderobject/CColorFlatObject.h"

namespace mx
{
	namespace scene
	{

		CColorFlatObject::CColorFlatObject(float fColor[4])
		{
			memcpy(m_fColor, fColor, 4 * sizeof(float));
		}

		CColorFlatObject::~CColorFlatObject()
		{

		}

		void CColorFlatObject::Create(IRenderable *pRenderable)
		{			
			IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
			if (pShaderProgram)
			{			
				pShaderProgram->CreateStandShader(ESS_SHADER_FLAT);
				pShaderProgram->SetUniform("vColor", m_fColor);
			}
		}

	}
}