#ifndef _RENDER_C_SOFT_SHADER_PROGRAM_H_
#define _RENDER_C_SOFT_SHADER_PROGRAM_H_

#include <map>

#include "render/IShaderProgram.h"
#include "CSoftVertexShader.h"
#include "CSoftFragmentShader.h"
#include "CPhongRender.h"

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
				ubyte *data;
				EDataType type;
				uint size;
			};

			typedef std::map<EUniformName, Uniform> UniformMap;

			CSoftShaderProgram(uint id);
			virtual ~CSoftShaderProgram();
			virtual uint GetID() const { return m_id; }
			virtual void SetUniform(EUniformName uniformName, const void *data, EDataType type, uint size);
			virtual ubyte *GetUniform(EUniformName uniformName);

		public:
			CSoftVertexShader *GetVertexShader() { return m_pVertexShader; }
			CSoftFragmentShader *GetFragmentShader() { return m_pFragShader; }
			const UniformMap &GetAllUniform() { return m_uniformMap; }
			void SetIllumination(CIllumination *pIllumination);
		private:
			uint m_id;
			UniformMap m_uniformMap;
			CSoftVertexShader *m_pVertexShader;
			CSoftFragmentShader *m_pFragShader;			
		};
	}
}

#endif