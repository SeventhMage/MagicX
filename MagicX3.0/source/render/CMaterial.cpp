#include "CMaterial.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CMaterial::CMaterial(int id)
			:m_id(id)
		{
			m_pShaderProgram = RENDERER->CreateShaderProgram();
		}

		CMaterial::~CMaterial()
		{			
			SAFE_DEL(m_pShaderProgram);
		}

		void CMaterial::BindConstantUniform()
		{
		}

	}
}