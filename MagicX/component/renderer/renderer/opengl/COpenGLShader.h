#ifndef _MX_RENDER_C_OPENGL_SHADER_H_
#define _MX_RENDER_C_OPENGL_SHADER_H_

#include "../../include/IShader.h"

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
			CString m_fileName;
			uint m_hShader;
			ShaderLang m_shaderLang;
			ShaderType m_shaderType;
		};
	}
}

#endif