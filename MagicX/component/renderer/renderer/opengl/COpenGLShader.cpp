#include "glew/GL/glew.h"
#include "COpenGLShader.h"
#include "OpenGLType.h"
#include "CFileStream.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{
		COpenGLShader::COpenGLShader()
		{

		}
		COpenGLShader::~COpenGLShader()
		{
			GLDebug(glDeleteShader(m_hShader));
		}
		
		uint COpenGLShader::Create(const char *filename, ShaderType type)
		{
			
			m_hShader = GLDebug(glCreateShader(GetGLShaderType(type)));
			io::CFileStream fileStream;
			if (fileStream.Open(filename))
			{
				const GLchar *data = (const GLchar *)fileStream.GetData();
				GLint length = fileStream.GetSize();
				GLDebug(glShaderSource(m_hShader, 1, &data, &length));
				m_fileName = filename;
			}
			return m_hShader;
		}
		
		bool COpenGLShader::Compile()
		{
			GLint testVal;
			GLDebug(glCompileShader(m_hShader));
			GLDebug(glGetShaderiv(m_hShader, GL_COMPILE_STATUS, &testVal));
			if (testVal == GL_FALSE)
			{
				char infoLog[1024];
				GLDebug(glGetShaderInfoLog(m_hShader, 1024, NULL, infoLog));
				printf("The Shader at %s failed to compile with the following error:%s\n", m_fileName.c_str(), infoLog);
				return false;
			}
			return true;
		}

	}
}