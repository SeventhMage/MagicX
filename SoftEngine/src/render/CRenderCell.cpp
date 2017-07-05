#include "CRenderCell.h"

namespace se
{
	namespace render
	{

		CRenderCell::CRenderCell()
			:m_materialId(0)
			, m_bufferId(0)
			, m_textureId(0)
			, m_pShaderProgram(nullptr)
		{

		}

		CRenderCell::~CRenderCell()
		{

		}

	}
}