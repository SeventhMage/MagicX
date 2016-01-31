#ifndef _MX_RENDER_C_OPENGL_SHADER_H_
#define _MX_RENDER_C_OPENGL_SHADER_H_

#include "render/IShader.h"
#include "mxType.h"
#include "mxDef.h"

namespace mx
{
	namespace render
	{
		class COpenGLShader : public IShader
		{
		public:
			COpenGLShader();
			virtual ~COpenGLShader();

			virtual uint Create(const char *filename, ShaderType type);
			virtual bool Compile();
			virtual uint GetHandle() { return m_hShader; }
			virtual ShaderLang GetShaderLang() { return SL_GLSL; }
		protected:
			char m_fileName[MAX_FILE_NAME];
			uint m_hShader;
			ShaderLang m_shaderLang;
			ShaderType m_shaderType;
		};
	}
}

#endif