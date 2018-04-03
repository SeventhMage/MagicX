#include "CSoftFragmentShader.h"

namespace se
{
	namespace render
	{


		CSoftFragmentShader::CSoftFragmentShader()
			:m_texData(nullptr)
			, m_texWidth(0)
		{
			m_pSampler = new CSampler();
		}

		CSoftFragmentShader::~CSoftFragmentShader()
		{
			delete m_pSampler;
		}

		const Color &CSoftFragmentShader::Process()
		{			
			static Color color(1, 1, 1, 1);	
			
			if (m_texData)
			{
				uint x = (uint)m_inTexCoord.x;
				uint y = (uint)m_inTexCoord.y;
												
				float inv = 1.f / 255;
				ubyte *temp = m_texData + y * m_texWidth * 3 + x * 3;
				color.a = 1.f;
				color.b = *(temp)* inv;
				color.g = *(temp + 1) * inv;
				color.r = *(temp + 2) * inv;
			}
			else
			{
				color.r = color.g = color.b = color.a = 1.f;
			}
			
			color.a *= m_inColor.a;
			color.r *= m_inColor.r;
			color.g *= m_inColor.g;
			color.b *= m_inColor.b;

			return color;

		}

		const Color & CSoftFragmentShader::Process(const Color &inColor, uint tx, uint ty)
		{
			static Color color(1, 1, 1, 1);

			if (m_texData)
			{
				float inv = 1.f / 255;
				ubyte *temp = m_texData + ty * m_texWidth * 3 + tx * 3;
				color.a = 1.f;
				color.b = *(temp)* inv;
				color.g = *(temp + 1) * inv;
				color.r = *(temp + 2) * inv;
			}
			else
			{
				color.r = color.g = color.b = color.a = 1.f;
			}

			color.a *= inColor.a;
			color.r *= inColor.r;
			color.g *= inColor.g;
			color.b *= inColor.b;			

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
				
				break;
			default:
				break;
			}
		}

		void CSoftFragmentShader::PushInAttribute(base::EVertexAttribute vertType, const void *source)
		{			
			switch (vertType)
			{
			case se::base::VA_COLOR:				
				m_inColor = *((Color *)source);
				break;
			case se::base::VA_TEXCOORD:
				memcpy(m_inTexCoord.v, source, sizeof(m_inTexCoord.v));
				m_inTexCoord = *((math::CVector2 *)source);
				break;
			case se::base::VA_NORMAL:
				
				break;
			default:
				break;
			}
		}

		void CSoftFragmentShader::SetTextureData(ubyte *texData, uint texWidth)
		{
			m_texData = texData;
			m_texWidth = texWidth;
		}

	}
}