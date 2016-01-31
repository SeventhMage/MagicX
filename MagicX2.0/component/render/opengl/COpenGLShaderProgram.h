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
			
			virtual bool Attach(const char *filename, ShaderType shaderType);
			virtual bool Attach(IShader *shader);
			virtual void Detach(IShader *shader);
			virtual bool Link();
			virtual uint GetHandle() { return m_hProgram; }

			virtual void BindUniform();
			virtual void BindAttributeLocation(int argc, ...);
		private:
			void GetShaderUniform();

			//���Ƽ���
			void GetShaderAttribute(); //�������Ӻ�ʹ������õ�����λ�ã����������ʹÿ��shader���򶼱���һ�ݻ���
		private:
			uint m_hProgram;
			IShader *m_pShader[ST_COUNT];
		};
	}
}
#endif // !_MX_RENDER_CSHADER_PROGRAM_H_
