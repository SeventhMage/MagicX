#include "CRenderCell.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{

		CRenderCell::CRenderCell(uint bufferId, uint materialId, uint textureId)
			:m_materialId(materialId)
			, m_bufferId(bufferId)
			, m_textureId(textureId)			
		{
			m_pShaderProgram = CSoftEngine::GetRenderer()->CreateShaderProgram();
		}

		CRenderCell::~CRenderCell()
		{
			SAFE_DEL(m_pShaderProgram);
		}

	}
}