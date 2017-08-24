#ifndef _RENDER_I_MATERIAL_H_
#define _RENDER_I_MATERIAL_H_

#include "math/CVector3.h"
#include "render/SColor.h"

#include <string>

namespace se
{
	namespace render
	{
		class IMaterial
		{
		public:
			virtual ~IMaterial(){}

			virtual int GetID() = 0;
			virtual std::string GetName() = 0;
			virtual Color GetColor() = 0;
			virtual void SetColor(const Color &color) = 0;
			virtual std::string GetIllumination() = 0;
			virtual void SetIllumination(const std::string &illumination) = 0;
		};
	}
}

#endif