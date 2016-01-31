#ifndef _I_SHADER_PROGRAM_H_
#define _I_SHADER_PROGRAM_H_

#include "IShader.h"

namespace mx
{
	namespace render
	{		
		class IShaderProgram
		{
		public:
			IShaderProgram(){};
			virtual ~IShaderProgram(){};
	
			virtual bool Attach(const char *filename, ShaderType shaderType) = 0;
			virtual bool Attach(IShader *shader) = 0;
			virtual void Detach(IShader *shader) = 0;
			virtual bool Link() = 0;			
			virtual void SetUniform(const char *name, void *value) = 0;
			virtual void SetUniform(int location, void *value) = 0;
			virtual void BindUniform() = 0;
			virtual void BindAttributeLocation(int argc, ...) = 0;
			virtual uint GetHandle() = 0;
		};
	}
}

#endif // !_I_SHADER_PROGRAM_H_
