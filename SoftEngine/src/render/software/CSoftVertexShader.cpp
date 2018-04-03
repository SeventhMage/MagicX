#include "CSoftVertexShader.h"

namespace se
{
	namespace render
	{


		CSoftVertexShader::CSoftVertexShader()
			:m_pIllumination(nullptr)
			, m_ambientCoefficient(0)
			, m_diffuseCoefficient(0)
			, m_specularCoefficient(0)
			, m_specularityCoefficient(0)
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

		math::CVector4 CSoftVertexShader::Process()
		{
			math::CMatrix4 mvMat = m_wordMatrix * m_viewMatrix;

			Color vColor = m_inColor;
			math::CVector2 vTexCoord = m_inTexCoord;

			math::CVector3 viewPosition;

			math::CVector4 outPosition;
			

			mvMat.TransformVect(viewPosition, m_inPosition);
			 
			math::CMatrix4 temp = m_viewMatrix;
			temp.SetTranslation(math::CVector3(0, 0, 0));
			math::CMatrix4 normalMatrix = m_normalMatrix * temp;
			
			normalMatrix.TransformVect(m_outNormal, m_inNormal);
			m_outNormal.normalize();

			vColor *= m_color;

			if (m_pIllumination)
			{							
				m_pIllumination->SetIlluminationParam(-viewPosition.Normalize(), m_outNormal);
				m_pIllumination->SetRenderParam(m_ambientCoefficient, m_diffuseCoefficient, m_specularCoefficient, m_specularityCoefficient);
				m_pIllumination->TransformPosition(m_viewMatrix);
				m_outColor = m_pIllumination->Shine(vColor, viewPosition);
			}

			m_outTexCoord = vTexCoord;

			m_projMatrix.TransformVect(outPosition, viewPosition);															

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
			case UN_NORMAL_MAT:
				memcpy(m_normalMatrix.m, data, sizeof(m_normalMatrix.m));
			case UN_COLOR:
				memcpy(m_color.c, data, sizeof(m_color.c));
				break;
			case UN_AMBIENT_COEFFICIENT:
				m_ambientCoefficient = *(float*)data;
				break;
			case UN_DIFFUSE_COEFFICIENT:
				m_diffuseCoefficient = *(float*)data;
				break;
			case UN_SPECULAR_COEFFICIENT:
				m_specularCoefficient = *(float*)data;
				break;
			case UN_SPECULARITY_COEFFICIENT:
				m_specularityCoefficient = *(int*)data;
				break;
			}
		}

		void CSoftVertexShader::PushInAttribute(base::EVertexAttribute vertType, const void *source)
		{
			switch (vertType)
			{			
			case se::base::VA_POSITION:				
				m_inPosition = *(math::CVector3* )source;
				break;
			case se::base::VA_COLOR:				
				m_inColor = *(Color *)source;
				break;
			case se::base::VA_TEXCOORD:
				m_inTexCoord = *(math::CVector2 *)source;
				break;
			case se::base::VA_NORMAL:
				m_inNormal = *(math::CVector3 *)source;
				break;
			default:
				break;
			}
		}

		void CSoftVertexShader::PopOutAttribute(base::EVertexAttribute vertType, void *&source)
		{
			switch (vertType)
			{
			case se::base::VA_POSITION:
				*(math::CVector3*)source = m_outPosition;
				break;
			case se::base::VA_COLOR:
				*(Color *)source = m_outColor;
				break;
			case se::base::VA_TEXCOORD:
				*(math::CVector2 *)source = m_outTexCoord;
				break;
			case se::base::VA_NORMAL:
				*(math::CVector3 *)source = m_outNormal;
				break;
			default:
				break;
			}
		}
	}
}