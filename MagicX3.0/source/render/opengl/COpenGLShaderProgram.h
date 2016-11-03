#ifndef _MX_RENDER_CSHADER_PROGRAM_H_
#define _MX_RENDER_CSHADER_PROGRAM_H_

#include "../CShaderProgram.h"

namespace mx
{
	namespace render
	{
		class COpenGLShaderProgram : public CShaderProgram
		{
		public:
			COpenGLShaderProgram();
			virtual ~COpenGLShaderProgram();
			virtual void CreateStandShader(E_STAND_SHADER standShader);
			virtual bool Attach(const char *filename, ShaderType shaderType);
			virtual bool Attach(IShader *shader);
			virtual bool AttachSource(const char *shaderSrc, ShaderType shaderType);
			virtual void Detach(IShader *shader);
			virtual bool Link();
			virtual uint GetHandle() { return m_hProgram; }

			virtual void Bind();
			virtual void BindAttributeLocation(int argc, ...);
		private:
			void GetShaderUniform();

			//不推荐的
			void GetShaderAttribute(); //程序链接后使用这个得到属性位置，但这样会会使每个shader程序都保存一份缓存
		private:
			uint m_hProgram;
			IShader *m_pShader[ST_COUNT];
		};
	}
}
#endif // !_MX_RENDER_CSHADER_PROGRAM_H_
