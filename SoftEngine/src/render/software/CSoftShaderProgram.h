#ifndef _RENDER_C_SOFT_SHADER_PROGRAM_H_
#define _RENDER_C_SOFT_SHADER_PROGRAM_H_

#include <map>

#include "render/IShaderProgram.h"
#include "CSoftVertexShader.h"
#include "CSoftFragmentShader.h"

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

			CSoftShaderProgram(uint id);
			virtual ~CSoftShaderProgram();
			virtual uint GetID() const { return m_id; }
			virtual void SetUniform(EUniformName uniformName, ubyte *data, uint size);
			virtual float *GetUniform(EUniformName uniformName);
		private:
			uint m_id;
			UniformMap m_uniformMap;
			CSoftVertexShader *m_pVertexShader;
			CSoftFragmentShader *m_pFragShader;
		};
	}
}

#endif