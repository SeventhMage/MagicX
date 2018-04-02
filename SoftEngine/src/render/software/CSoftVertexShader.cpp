#include "CSoftVertexShader.h"

namespace se
{
	namespace render
	{


		CSoftVertexShader::CSoftVertexShader()
			:m_pIllumination(nullptr)
		{

		}

		CSoftVertexShader::~CSoftVertexShader()
		{

		}

		math::CVector4 CSoftVertexShader::Process(const IShaderAttribute &attrInput, IShaderAttribute &attrOutput)
		{
			const ShaderAttrData &inPositon = attrInput.GetAttribute(base::VA_POSITION);
			const ShaderAttrData &inNormal = attrInput.GetAttribute(base::VA_NORMAL);
			const ShaderAttrData &inColor = attrInput.GetAttribute(base::VA_COLOR);
			const ShaderAttrData &inTexCoord = attrInput.GetAttribute(base::VA_TEXCOORD);
			
			math::CMatrix4 mvpMat = m_wordMatrix * m_viewMatrix * m_projMatrix;

			math::CVector3 vPosition;
			math::CVector3 vNormal;
			render::SColor vColor;
			math::CVector2 vTexCoord;


			math::CVector4 outPosition;
			math::CVector3 outNormal;

			if (inPositon.vertType != base::VA_NONE)
				memcpy(vPosition.v, inPositon.data, sizeof(vPosition.v));
			if (inNormal.vertType != base::VA_NONE)
				memcpy(vNormal.v, inNormal.data, sizeof(vNormal.v));
			if (inColor.vertType != base::VA_NONE)
				memcpy(vColor.c, inColor.data, sizeof(vColor.c));
			if (inTexCoord.vertType != base::VA_NONE)
				memcpy(vTexCoord.v, inTexCoord.data, sizeof(vTexCoord.v));
			
			
			mvpMat.TransformVect(outPosition, vPosition);
			
			math::CMatrix4 temp;
			mvpMat.GetInverse(temp);
			math::CMatrix4 normalMatrix;
			temp.GetTransposed(normalMatrix);
			normalMatrix.SetTranslation(math::CVector3(0, 0, 0));
			m_wordMatrix.TransformVect(outNormal, vPosition);

			vColor *= m_color;			
			
			attrOutput.SetAttribute(base::VA_NORMAL, vNormal.v, sizeof(vNormal.v));
			attrOutput.SetAttribute(base::VA_COLOR, vColor.c, sizeof(vColor.c));
			attrOutput.SetAttribute(base::VA_TEXCOORD, vTexCoord.v, sizeof(vTexCoord.v));

			return outPosition;
		}

		math::CVector4 CSoftVertexShader::Process(IShaderAttribute &attrOutput)
		{
			math::CMatrix4 mvpMat = m_wordMatrix * m_viewMatrix * m_projMatrix;

			render::SColor vColor = m_inColor;
			math::CVector2 vTexCoord = m_inTexCoord;

			math::CVector4 outPosition;
			math::CVector3 outNormal;

			mvpMat.TransformVect(outPosition, m_inPosition);

			math::CMatrix4 temp;
			mvpMat.GetInverse(temp);
			math::CMatrix4 normalMatrix;
			temp.GetTransposed(normalMatrix);
			normalMatrix.SetTranslation(math::CVector3(0, 0, 0));
			m_wordMatrix.TransformVect(outNormal, m_inNormal);

			vColor *= m_color;

			attrOutput.SetAttribute(base::VA_NORMAL, outNormal.v, sizeof(outNormal.v));
			attrOutput.SetAttribute(base::VA_COLOR, vColor.c, sizeof(vColor.c));
			attrOutput.SetAttribute(base::VA_TEXCOORD, vTexCoord.v, sizeof(vTexCoord.v));

			return outPosition;
		}

		void CSoftVertexShader::SetUniform(EUniformName uniformName, ubyte *data)
		{
			switch (uniformName)
			{
			case UN_WORLD_MAT:
				memcpy(m_wordMatrix.m, data, sizeof(m_wordMatrix.m));
				break;
			case UN_VIEW_MAT:
				memcpy(m_viewMatrix.m, data, sizeof(m_viewMatrix.m));
				break;
			case UN_PROJ_MAT:
				memcpy(m_projMatrix.m, data, sizeof(m_projMatrix.m));
				break;
			case UN_COLOR:
				memcpy(m_color.c, data, sizeof(m_color.c));
				break;
			}
		}

		void CSoftVertexShader::PushInAttribute(base::EVertexAttribute vertType, const void *source)
		{
			switch (vertType)
			{			
			case se::base::VA_POSITION:
				memcpy(m_inPosition.v, source, sizeof(m_inPosition.v));
				break;
			case se::base::VA_COLOR:
				memcpy(m_inColor.c, source, sizeof(m_inColor.c));
				break;
			case se::base::VA_TEXCOORD:
				memcpy(m_inTexCoord.v, source, sizeof(m_inTexCoord.v));
				break;
			case se::base::VA_NORMAL:
				memcpy(m_inNormal.v, source, sizeof(m_inNormal.v));
				break;
			default:
				break;
			}
		}

	}
}