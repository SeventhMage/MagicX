#include "scene/renderobject/CColorFlatObject.h"

namespace mx
{
	namespace scene
	{

		CColorFlatObject::CColorFlatObject(float fColor[4])
		{
			//Create(fColor);
		}

		CColorFlatObject::~CColorFlatObject()
		{

		}

		void CColorFlatObject::Create(IRenderable *pRenderable)
		{
			if (!m_pVAO) return;
			
			IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
			if (pShaderProgram)
			{			
				pShaderProgram->CreateStandShader(ESS_SHADER_FLAT);
				float color[] = { 1, 1, 0, 1 };
				pShaderProgram->SetUniform("vColor", color);
			}
		}

	}
}