#ifndef _SE_SCENE_I_DIRETIONAL_LIGHT_H_
#define _SE_SCENE_I_DIRETIONAL_LIGHT_H_

#include "ILight.h"
#include "math/CVector3.h"

namespace se
{
    namespace scene
    {
        class IDirectionalLight : public ILight
        {
        public:
            virtual ELightType GetLightType(){ return LT_DIRECTIONAL; }
            virtual void SetPosition(const math::CVector3 &) = 0;
            virtual const math::CVector3 &GetPosition() const = 0;
            virtual void SetDirection(const math::CVector3 &) = 0;
            virtual const math::CVector3 &GetDirection() = 0;
        };
    }
}

#endif
