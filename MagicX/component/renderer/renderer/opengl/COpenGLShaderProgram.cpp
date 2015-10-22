#include "COpenGLShaderProgram.h"
#include "glew/GL/glew.h"
#include "COpenGLShader.h"

namespace mx
{
	namespace render
	{
		

		COpenGLShaderProgram::COpenGLShaderProgram()
		{
			m_hProgram = glCreateProgram();
		}

		COpenGLShaderProgram::~COpenGLShaderProgram()
		{
			for (uint i = 0; i < ST_COUNT; ++i)
			{
				glDetachShader(m_hProgram, m_pShader[i]->GetHandle());
				SAFE_DEL(m_pShader[i]);
			}
			glDeleteProgram(m_hProgram);
		}
		
		bool COpenGLShaderProgram::Attach(IShader *shader)
		{
			if (shader)
			{
				glAttachShader(m_hProgram, shader->GetHandle());
				return true;
			}
			return false;
		}

		bool COpenGLShaderProgram::Attach(const char *filename, ShaderType shaderType)
		{
			if (shaderType >=0  && shaderType < ST_COUNT)
			{
				m_pShader[shaderType] = new COpenGLShader();
				m_pShader[shaderType]->Create(filename, shaderType);
				m_pShader[shaderType]->Compile();
				glAttachShader(m_hProgram, m_pShader[shaderType]->GetHandle());
			}			
			return true;
		}


		void COpenGLShaderProgram::Detach(IShader *shader)
		{
			if (shader)
			{
				glDetachShader(m_hProgram, shader->GetHandle());
			}
		}
		
		bool COpenGLShaderProgram::Link()
		{
			glBindAttribLocation(m_hProgram, VAI_VERTEX, "position");
			//glBindAttribLocation(m_hProgram, VAI_COLOR, "inColor");
			glBindAttribLocation(m_hProgram, VAI_TEXTURE1, "vTexCoord0");
			//////////////////////////////////////////////////////////////////////////

			GLint testVal;
			glLinkProgram(m_hProgram);
			glGetProgramiv(m_hProgram, GL_LINK_STATUS, &testVal);
			if (testVal == GL_FALSE)
			{
				char infoLog[1024];
				glGetProgramInfoLog(m_hProgram, 1024, NULL, infoLog);
				printf("The program %d failed to link with the following error:%s\n", m_hProgram, infoLog);
				return false;
			}
			return true;
		}

		void COpenGLShaderProgram::setUniform(const char *name, UniformFormat format, void *value)
		{

		}

	}
}