#include "GL/glew.h"
#include "COpenGLShader.h"
#include "OpenGLType.h"
#include "GLDebug.h"

#include <fstream>
#include <sys/stat.h>

namespace mx
{
	namespace render
	{
		COpenGLShader::COpenGLShader()
			:m_hShader(0)
			, m_shaderLang(SL_GLSL)
			, m_shaderType(ST_INVALID)
		{
			memset(m_fileName, 0, sizeof(m_fileName));
		}
		COpenGLShader::~COpenGLShader()
		{
			GLDebug(glDeleteShader(m_hShader));
		}
		
		uint COpenGLShader::Create(const char *filename, ShaderType type)
		{			
			m_hShader = GLDebug(glCreateShader(GetGLShaderType(type)));

			struct stat tagStat;
			int ret = stat(filename, &tagStat);
			if (ret == 0)
			{
				std::ifstream stream;
				stream.open(filename, std::ios::in | std::ios::binary);
				if (!stream.fail())
				{
					uint size = tagStat.st_size + 1;
					byte *data = new byte[size];

					stream.read((char *)data, size);
					data[size - 1] = 0;
					const GLchar *glData = (const GLchar *)data;
					GLint length = (GLint)size;
					GLDebug(glShaderSource(m_hShader, 1, &glData, &length));
					strncpy(m_fileName, filename, MAX_FILE_NAME - 1);
					delete[]data;
				}

			}
			return m_hShader;
		}

		uint COpenGLShader::CreateBySource(const char *shaderSource, ShaderType type)
		{
			m_hShader = GLDebug(glCreateShader(GetGLShaderType(type)));
			GLchar *fsStringPtr[1];
			fsStringPtr[0] = (GLchar *)shaderSource;
			glShaderSource(m_hShader, 1, (const GLchar **)fsStringPtr, NULL);
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
				printf("The Shader at %s failed to compile with the following error:%s\n", m_fileName, infoLog);
				return false;
			}
			return true;
		}

	}
}