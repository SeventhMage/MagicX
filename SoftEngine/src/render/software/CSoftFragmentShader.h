#ifndef _SE_RENDER_C_SOFT_FRAGMENT_SHADER_H_
#define _SE_RENDER_C_SOFT_FRAGMENT_SHADER_H_

#include "render/IShader.h"
#include "render/IIllumination.h"
#include "render/ISampler.h"

namespace se
{
	namespace render
	{
		class CSoftFragmentShader : public IShader
		{
		public:
			CSoftFragmentShader();
			virtual ~CSoftFragmentShader();

			virtual EShaderType GetType() const { return ST_FRAGMENT; }

			virtual Color Process(const IShaderAttribute &attrInput);
			virtual void SetUniform(EUniformName uniformName, ubyte *data);
			virtual void SetIllumination(IIllumination *illumination) {}
		private:
			uint m_textureUnit;
			ISampler *m_pSampler;
		};
	}
}

#endif