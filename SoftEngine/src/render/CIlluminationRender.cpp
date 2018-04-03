#include "CIlluminationRender.h"

namespace se
{
	namespace render
	{


		CIlluminationRender::CIlluminationRender()	
			: m_ambientCoefficient(0)
			, m_diffuseCoefficient(0)
			, m_specularCoefficient(0)
			, m_specularityCoefficient(0)
		{

		}

		CIlluminationRender::~CIlluminationRender()
		{

		}

		Color CIlluminationRender::CalcIllumination(const Color &srcColor)
		{
			return srcColor;
		}


		void CIlluminationRender::SetRenderParam(float ambientCoefficient, float diffuseCoefficient, float specularCoefficient, int specularityCoefficient)
		{
			m_ambientCoefficient = ambientCoefficient;
			m_diffuseCoefficient = diffuseCoefficient;
			m_specularCoefficient = specularCoefficient;
			m_specularityCoefficient = specularityCoefficient;
		}

	}
}