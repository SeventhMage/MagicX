#include "CPhongRender.h"
#include "base/seDef.h"

#include <math.h>

namespace se
{
    namespace render
    {
		CPhongRender::CPhongRender()
        {
        }
		CPhongRender::~CPhongRender()
        {
            
        }       

		Color CPhongRender::CalcIllumination(const Color &srcColor, const math::CVector3 &viewDir, const math::CVector3 &normalDir)
		{
			render::SColor ambient = m_ambientColor * m_ambientCoefficient;
			render::SColor diffuse = m_diffuseColor * m_diffuseCoefficient * (MAX(m_IlluminationDir.dotProduct(normalDir), 0));

			//math::CVector3 r = 2 * (m_IlluminationDir.dotProduct(normalDir)) * normalDir - m_IlluminationDir;
			math::CVector3 h = viewDir + m_IlluminationDir;
			h.normalize();
			render::SColor specual = m_specularColor * m_specularCoefficient * pow(MAX(h.dotProduct(viewDir), 0), m_specularityCoefficient);

			float decay = 1 / (m_IlluminationDis * 0.00025f);

			render::SColor lightColor = ambient + (diffuse + specual) * decay;

			return render::SColor(1.f, MIN(lightColor.r * srcColor.r, 1), MIN(lightColor.g * srcColor.g, 1), MIN(lightColor.b * srcColor.b, 1));
			
		}

		void CPhongRender::SetLightColor(const Color &ambientColor, const Color &diffuseColor, const Color &specularColor)
		{
			m_ambientColor = ambientColor;
			m_diffuseColor = diffuseColor;
			m_specularColor = specularColor;
		}


    }
}
