#ifndef _SE_SCENE_I_AMBIENT_LIGHT_H_
#define _SE_SCENE_I_AMBIENT_LIGHT_H_

#include "ILight.h"

namespace se
{
    namespace scene
    {
        class IAmbientLight : public ILight
        {
        public:
            virtual ELightType GetLightType(){ return LT_AMBIENT; }
        };
    }
}

#endif
