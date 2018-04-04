/*
 * Calculate the illumination
 */

#ifndef _RENDER_C_PHONG_RENDER_H_
#define _RENDER_C_PHONG_RENDER_H_

#include "render/SColor.h"
#include "math/CVector3.h"
#include "../CIlluminationRender.h"

namespace se
{
    namespace render
    {
		class CPhongRender : public CIlluminationRender
        {
        public:
			CPhongRender();
			~CPhongRender();
            
			virtual Color CalcIllumination(const Color &srcColor, const math::CVector3 &viewDir, const math::CVector3 &normalDir);

			void SetLightColor(const Color &ambientColor, const Color &diffuseColor, const Color &specularColor);									        
        private:
            Color m_ambientColor;
            Color m_diffuseColor;
            Color m_specularColor;
        };
    }
}

#endif
