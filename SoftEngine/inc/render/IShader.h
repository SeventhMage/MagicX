#ifndef _SE_RENDER_I_SHADER_H_
#define _SE_RENDER_I_SHADER_H_

#include "IShaderAttribute.h"
#include "UniformDef.h"
#include "IIllumination.h"

namespace se
{
	namespace render
	{
		enum EShaderType
		{
			ST_VERTEX = 0,
			ST_FRAGMENT,

			ST_COUNT,
		};

		class IShader
		{
		public:
			virtual ~IShader(){}
			virtual EShaderType GetType() const = 0;			
			virtual void SetUniform(EUniformName uniformName, ubyte *data) = 0;
			virtual void SetIllumination(IIllumination *illumination) {}
			virtual void PushInAttribute(base::EVertexAttribute vertType, const void *source) = 0;
		};
	}
}

#endif