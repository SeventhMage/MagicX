/*
 * Calculate the illumination
 */

#ifndef _RENDER_C_ILLUMINATION_RENDER_H_
#define _RENDER_C_ILLUMINATION_RENDER_H_

#include "render/SColor.h"
#include "math/CVector3.h"

namespace se
{
    namespace render
    {
        class CIlluminationRender
        {
        public:
            CIlluminationRender(const render::SColor &ambientColor, const render::SColor &diffuseColor, const render::SColor &specularColor);
            ~CIlluminationRender();
            
            render::SColor Calculate(const render::SColor &srcColor, const math::CVector3 &lightDir, const math::CVector3 &viewDir, const math::CVector3 &normalDir, float ambientCoefficient, float diffuseCoefficient, float specularCoefficient, int specularityCoefficient, float lightDistance);
        private:
            render::SColor m_ambientColor;
            render::SColor m_diffuseColor;
            render::SColor m_specularColor;
        
            
        };
    }
}

#endif
