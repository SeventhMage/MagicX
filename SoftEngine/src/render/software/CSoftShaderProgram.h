#ifndef _RENDER_C_SOFT_SHADER_PROGRAM_H_
#define _RENDER_C_SOFT_SHADER_PROGRAM_H_

#include "render/IShaderProgram.h"

#include <map>

namespace se
{
	namespace render
	{
		class CSoftShaderProgram : public IShaderProgram
		{
		public:
			struct Uniform
			{
				EUniformName name;
				float *data;
			};

			typedef std::map<uint, Uniform> UniformMap;

			CSoftShaderProgram();
			virtual ~CSoftShaderProgram();

			virtual void SetUniform(EUniformName uniformName, ubyte *data, uint size);
			virtual float *GetUniform(EUniformName uniformName);
		private:
			UniformMap m_uniformMap;
		};
	}
}

#endif