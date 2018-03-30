#include "CSoftFragmentShader.h"
#include "CSampler.h"

namespace se
{
	namespace render
	{


		CSoftFragmentShader::CSoftFragmentShader()
			:m_textureUnit(0)			
		{
			m_pSampler = new CSampler();
		}

		CSoftFragmentShader::~CSoftFragmentShader()
		{
			delete m_pSampler;
		}

		Color CSoftFragmentShader::Process(const IShaderAttribute &attrInput)
		{			
			const ShaderAttrData &inTexCoord = attrInput.GetAttribute(base::VA_TEXCOORD);
			const ShaderAttrData &inColor = attrInput.GetAttribute(base::VA_COLOR);

			Color color(1, 1, 1, 1);
			if (m_pSampler && m_textureUnit > 0)
			{
				math::CVector2 vTexCoord;
				memcpy(vTexCoord.v, inTexCoord.data, sizeof(vTexCoord.v));
				color = m_pSampler->GetColor(m_textureUnit, vTexCoord);
			}

			Color sColor;
			memcpy(sColor.c, inColor.data, sizeof(sColor.c));

			color *= sColor;

			return color;
		}

		void CSoftFragmentShader::SetUniform(EUniformName uniformName, ubyte *data)
		{
			switch (uniformName)
			{			
			case se::render::UN_TEXTURE_0:				
			case se::render::UN_TEXTURE_1:				
			case se::render::UN_TEXTURE_2:				
			case se::render::UN_TEXTURE_3:
				memcpy(&m_textureUnit, data, sizeof(m_textureUnit));
			default:
				break;
			}
		}

	}
}