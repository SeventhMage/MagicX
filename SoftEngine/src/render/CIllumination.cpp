#include "CIllumination.h"

namespace se
{
	namespace render
	{

		CIllumination::CIllumination(CIlluminationRender *pIlluminationRender)
			:m_pIlluminationRender(pIlluminationRender)
		{

		}

		CIllumination::~CIllumination()
		{

		}

		se::render::Color CIllumination::Shine(const Color &srcColor, const math::CVector3 &targetPoint, const math::CVector3 &viewDir, const math::CVector3 &normalDir)
		{
			if (m_pIlluminationRender)
			{
				m_pIlluminationRender->SetIlluminationDir((m_transPositoin - targetPoint).normalize());
				m_pIlluminationRender->SetIlluminationDis(m_transPositoin.getDistanceFromSQ(targetPoint));
				return  m_pIlluminationRender->CalcIllumination(srcColor, viewDir, normalDir);
			}
			return srcColor;
		}

		void CIllumination::SetRenderParam(float ambientCoefficient, float diffuseCoefficient, float specularCoefficient, int specularityCoefficient)
		{
			if (m_pIlluminationRender)
			{
				m_pIlluminationRender->SetRenderParam(ambientCoefficient, diffuseCoefficient, specularCoefficient, specularityCoefficient);
			}
		}

		void CIllumination::TransformPosition(const math::CMatrix4 &viewMat)
		{
			viewMat.TransformVect(m_transPositoin, m_position);
		}

	}
}