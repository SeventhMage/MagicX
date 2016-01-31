#ifndef _I_SHADER_H_INC_
#define _I_SHADER_H_INC_

#include "ERender.h"
#include "mxType.h"

namespace mx
{
	namespace render
	{
		class IShader
		{
		public:
			IShader(){};
			virtual ~IShader(){};
			
			virtual uint Create(const char *filename, ShaderType shaderTpe) = 0;
			virtual bool Compile() = 0;
			virtual uint GetHandle() = 0;
			virtual ShaderLang GetShaderLang() = 0;
			
		};
	}
}

#endif // !_I_SHADER_H_INC_
