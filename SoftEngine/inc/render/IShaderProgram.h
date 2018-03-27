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

			virtual uint GetID() const = 0;
			virtual void SetUniform(EUniformName uniformName, const void *data, EDataType type, uint size) = 0;
			virtual byte *GetUniform(EUniformName uniformName) = 0;			
		};
	}
}

#endif