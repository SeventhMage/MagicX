#ifndef _RENDER_I_MATERIAL_H_
#define _RENDER_I_MATERIAL_H_

#include <string>

#include "math/CVector3.h"
#include "render/SColor.h"
#include "IShaderProgram.h"

namespace se
{
	namespace render
	{
		class IMaterial
		{
		public:
			virtual ~IMaterial(){}

			virtual uint GetID() = 0;
			virtual std::string GetName() = 0;
			virtual Color GetColor() = 0;
			virtual void SetColor(const Color &color) = 0;
			virtual std::string GetIllumination() = 0;
			virtual void SetIllumination(const std::string &illumination) = 0;
			virtual IShaderProgram *GetShaderProgram() const = 0;
			virtual uint GetShaderProgramID() const = 0;
		};
	}
}

#endif