#include "CRenderer.h"

namespace se
{
	namespace render
	{

		CRenderer::CRenderer()
			:m_shaderProgramId(0)
			, m_vaoId(0)
			, m_bufferId(0)
			, m_textureId(0)
		{

		}

		void CRenderer::UseShaderProgram(uint shaderProgramId)
		{
			m_shaderProgramId = shaderProgramId;
		}

		void CRenderer::EnableVertexArrayObject(uint vaoId)
		{
			m_vaoId = vaoId;
		}

		void CRenderer::BindBuffer(uint bufferId)
		{
			m_bufferId = bufferId;
		}

		void CRenderer::BindTexture(uint textureId)
		{
			m_textureId = textureId;
		}

	}
}