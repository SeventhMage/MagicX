#ifndef _SE_SCENE_I_SPOT_LIGHT_H_
#define _SE_SCENE_I_SPOT_LIGHT_H_

#include "ILight.h"
#include "math/CVector3.h"

namespace se
{
    namespace scene
    {
        class ISpotLight : public ILight
        {
        public:
            virtual ELightType GetLightType(){ return LT_SPOT; }
            virtual void SetPosition(const math::CVector3 &) =  0;
            virtual const math::CVector3 &GetPosition() const = 0;
            virtual void SetSemiangle(float angle) = 0;
            virtual float GetSemiangle() const = 0;
        };
    }
}

#endif
