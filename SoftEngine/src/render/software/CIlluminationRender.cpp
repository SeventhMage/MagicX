#include "CIlluminationRender.h"
#include "base/seDef.h"

#include <math.h>

namespace se
{
    namespace render
    {
        CIlluminationRender::CIlluminationRender(const render::SColor &ambientColor, const render::SColor &diffuseColor, const render::SColor &specularColor)
        :m_ambientColor(ambientColor)
        ,m_diffuseColor(diffuseColor)
        ,m_specularColor(specularColor)
        {
        }
        CIlluminationRender::~CIlluminationRender()
        {
            
        }
        
        render::SColor CIlluminationRender::Calculate(const render::Color &srcColor, const math::CVector3 &lightDir, const math::CVector3 &viewDir, const math::CVector3 &normalDir, float ambientCoefficient, float diffuseCoefficient, float specularCoefficient, int specularityCoefficient, float lightDistance)
        {
            render::SColor ambient = m_ambientColor * ambientCoefficient;
            render::SColor diffuse = m_diffuseColor * diffuseCoefficient * (MAX(lightDir.dotProduct(normalDir), 0));
            
            math::CVector3 r = 2 * (lightDir.dotProduct(normalDir)) * normalDir - lightDir;
            render::SColor specual = m_specularColor * specularCoefficient * pow(MAX(r.dotProduct(viewDir), 0), specularityCoefficient);
            
            float decay = 1; //1 / lightDistance;
            
            render::SColor lightColor = ambient + (diffuse + specual) * decay;
            
            return render::SColor(1.f, MIN(lightColor.r * srcColor.r, 1), MIN(lightColor.g * srcColor.g, 1), MIN(lightColor.b * srcColor.b, 1));
        }

    }
}
