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

		math::CVector4 &CSoftVertexShader::Process()
		{
			static math::CMatrix4 mvMat;
			mvMat = m_wordMatrix * m_viewMatrix;

			Color vColor = *m_inColor;
			math::CVector2 vTexCoord = *m_inTexCoord;

			static math::CVector3 viewPosition;
			static math::CVector3 viewDir;

			static math::CVector4 outPosition;			

			mvMat.TransformVect(viewPosition, *m_inPosition);

			viewDir.x = -viewPosition.x;
			viewDir.y = -viewPosition.y;
			viewDir.z = -viewPosition.z;

			viewDir.normalize();
			 
			math::CMatrix4 temp = m_viewMatrix;
			temp.SetTranslation(0, 0, 0);
			static math::CMatrix4 normalMatrix;
			normalMatrix = m_normalMatrix * temp;
			
			normalMatrix.TransformVect(m_outNormal, *m_inNormal);
			m_outNormal.normalize();

			vColor *= m_color;

			if (m_pIllumination)
			{				
				m_pIllumination->SetRenderParam(m_ambientCoefficient, m_diffuseCoefficient, m_specularCoefficient, m_specularityCoefficient);
				m_pIllumination->TransformPosition(m_viewMatrix);
				m_outColor = m_pIllumination->Shine(vColor, viewPosition, viewDir, m_outNormal);
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
				m_inPosition = (math::CVector3 *)source;
				break;
			case se::base::VA_COLOR:												
				m_inColor = (Color *)source;
				break;
			case se::base::VA_TEXCOORD:				
				m_inTexCoord = (math::CVector2 *)source;
				break;
			case se::base::VA_NORMAL:				
				m_inNormal = (math::CVector3 *)source;
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
				memcpy(source, m_outPosition.v, sizeof(m_outPosition.v));
				break;
			case se::base::VA_COLOR:
				*(Color *)source = m_outColor;
				memcpy(source, m_outColor.c, sizeof(m_outColor.c));
				break;
			case se::base::VA_TEXCOORD:				
				memcpy(source, m_outTexCoord.v, sizeof(m_outTexCoord.v));
				break;
			case se::base::VA_NORMAL:				
				memcpy(source, m_outNormal.v, sizeof(m_outNormal.v));
				break;
			default:
				break;
			}
		}
	}
}