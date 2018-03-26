#include "CSoftFragmentShader.h"

namespace se
{
	namespace render
	{


		CSoftFragmentShader::CSoftFragmentShader(ISampler *pSampler /* = nullptr */)
			:m_textureUnit(0)
			, m_pSampler(pSampler)
		{

		}

		CSoftFragmentShader::~CSoftFragmentShader()
		{

		}

		Color CSoftFragmentShader::Process(const IShaderAttribute &attrInput, IShaderAttribute &attrOutput)
		{			
			const ShaderAttrData &inTexCoord = attrInput.GetAttribute(base::VA_TEXCOORD);
			const ShaderAttrData &inColor = attrInput.GetAttribute(base::VA_COLOR);

			Color color(1, 1, 1, 1);
			if (m_pSampler)
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