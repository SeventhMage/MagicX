#include "COpenGLShaderProgram.h"
#include "glew/GL/glew.h"
#include "COpenGLShader.h"
#include "OpenGLType.h"
#include "GLDebug.h"
#include "../../Include/SVertexAttribute.h"

#include <stdarg.h>

namespace mx
{
	namespace render
	{
		

		COpenGLShaderProgram::COpenGLShaderProgram()
		{
			m_hProgram = GLDebug(glCreateProgram());
		}

		COpenGLShaderProgram::~COpenGLShaderProgram()
		{
			for (uint i = 0; i < ST_COUNT; ++i)
			{
				if (m_pShader[i])
				{
					GLDebug(glDetachShader(m_hProgram, m_pShader[i]->GetHandle()));
					SAFE_DEL(m_pShader[i]);
				}				
			}
			GLDebug(glDeleteProgram(m_hProgram));
		}
		
		bool COpenGLShaderProgram::Attach(IShader *shader)
		{
			if (shader)
			{
				GLDebug(glAttachShader(m_hProgram, shader->GetHandle()));
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
				GLDebug(glAttachShader(m_hProgram, m_pShader[shaderType]->GetHandle()));
			}			
			return true;
		}


		void COpenGLShaderProgram::Detach(IShader *shader)
		{
			if (shader)
			{
				GLDebug(glDetachShader(m_hProgram, shader->GetHandle()));
			}
		}
		
		bool COpenGLShaderProgram::Link()
		{
			GLint testVal;
			GLDebug(glLinkProgram(m_hProgram));
			GLDebug(glGetProgramiv(m_hProgram, GL_LINK_STATUS, &testVal));
			if (testVal == GL_FALSE)
			{
				char infoLog[1024];
				glGetProgramInfoLog(m_hProgram, 1024, NULL, infoLog);
				printf("The program %d failed to link with the following error:%s\n", m_hProgram, infoLog);
				return false;
			}

			GetShaderUniform();		

			return true;
		}

		void COpenGLShaderProgram::BindUniform()
		{
			CShaderProgram::UniformArray::iterator it = m_uniforms.begin();
			for (; it != m_uniforms.end(); ++it)
			{
				Uniform &uniform = it->second;
				if (uniform.IsDirty())
				{
					switch (uniform.m_format)
					{
					case UF_FLOAT:
						GLDebug(glUniform1fv(uniform.m_location, uniform.m_count, (GLfloat *)uniform.m_value));
						break;
					case UF_INT:
						GLDebug(glUniform1iv(uniform.m_location, uniform.m_count, (GLint *)uniform.m_value));
						break;
					case UF_VEC2:
						GLDebug(glUniform2fv(uniform.m_location, uniform.m_count, (GLfloat *)uniform.m_value));
						break;
					case UF_VEC3:
						GLDebug(glUniform3fv(uniform.m_location, uniform.m_count, (GLfloat *)uniform.m_value));
						break;
					case UF_VEC4:
						GLDebug(glUniform4fv(uniform.m_location, uniform.m_count, (GLfloat *)uniform.m_value));
						break;
					case UF_MAT4:
						GLDebug(glUniformMatrix4fv(uniform.m_location, uniform.m_count, GL_FALSE, (GLfloat *)uniform.m_value));
						break;
					case UF_TEXTURE:
						break;
					default:
						break;
					}
					uniform.Dirty(false);
				}			
			}
		}

		void COpenGLShaderProgram::GetShaderUniform()
		{
			//glGetProgramInterface ÐÂ·½Ê½
			GLint uniformsNum = 0;
			GLDebug(glGetProgramiv(m_hProgram, GL_ACTIVE_UNIFORMS, &uniformsNum));
			if (uniformsNum > 0)
			{
				GLint maxLength;
				GLDebug(glGetProgramiv(m_hProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength));
				char *name = new char[maxLength];
				for (int i = 0; i < uniformsNum; ++i)
				{

					Uniform uniform;

					GLenum type;
					GLsizei nameLength;
					GLDebug(glGetActiveUniform(m_hProgram, i, maxLength, &nameLength, &uniform.m_count, &type, name));
					uniform.m_format = GetUniformFormat(type);
					uniform.m_name = name;
					uniform.m_size = GetUniformTypeSize(uniform.m_format);
					uniform.m_location = i;

					m_uniforms[i] = uniform;
				}
				delete name;
			}
		}

		void COpenGLShaderProgram::GetShaderAttribute()
		{
			GLint attrNum;
			GLDebug(glGetProgramiv(m_hProgram, GL_ACTIVE_ATTRIBUTES, &attrNum));
			if (attrNum)
			{

			}
		}

		void COpenGLShaderProgram::BindAttributeLocation(int argc, ...)
		{
			va_list argp;
		
			int location;

			va_start(argp, argc);

			for (int i = 0; i < argc; ++i)
			{
				location = va_arg(argp, int);
				GLDebug(glBindAttribLocation(m_hProgram, location, g_sVertexAttributeArray[location].attrName));
			}
			va_end(argp);
		}

	}
}