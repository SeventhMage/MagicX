#include "CMaterial.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CMaterial::CMaterial()
			:m_eIllumination(IM_PHONE)
			, m_fSpecularCoefficient(0)
			, m_fSpecularIndex(0)
			, m_fAmbientCoefficient(0)
			, m_fDiffuseCoefficient(0)
			, m_fReflectR(1.f)
			, m_fReflectG(1.f)
			, m_fReflectB(1.f)
		{			
		}

		CMaterial::~CMaterial()
		{			
		}

		void CMaterial::SetReflectColor(float r, float g, float b)
		{
			m_fReflectR = r; 
			m_fReflectG = g; 
			m_fReflectB = b;
		}

	}
}