#ifndef _RENDER_I_SHADER_PROGRAM_H_
#define _RENDER_I_SHADER_PROGRAM_H_

#include "UniformDef.h"

namespace se
{
	namespace render
	{
		class IShaderProgram
		{
		public:
			virtual ~IShaderProgram(){};

			virtual void SetUniform(EUniformName uniformName, ubyte *data, uint size) = 0;
			virtual float *GetUniform(EUniformName uniformName) = 0;
		};
	}
}

#endif