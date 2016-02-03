#include "COpenGLShaderProgram.h"
#include "glew/GL/glew.h"
#include "COpenGLShader.h"
#include "OpenGLType.h"
#include "GLDebug.h"
#include "render/SVertexAttribute.h"

#include <stdarg.h>

namespace mx
{
	namespace render
	{
		///////////////////////////////////////////////////////////////////////////////
		// Identity Shader (ESS_SHADER_IDENTITY)
		// This shader does no transformations at all, and uses the current
		// glColor value for fragments.
		// It will shade between verticies.
		static const char *szIdentityShaderVP = "attribute vec4 vVertex;"
			"void main(void) "
			"{ gl_Position = vVertex; "
			"}";

		static const char *szIdentityShaderFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"uniform vec4 vColor;"
			"void main(void) "
			"{ gl_FragColor = vColor;"
			"}";


		///////////////////////////////////////////////////////////////////////////////
		// Flat Shader (ESS_SHADER_FLAT)
		// This shader applies the given model view matrix to the verticies, 
		// and uses a uniform color value.
		static const char *szFlatShaderVP = "uniform mat4 mvpMatrix;"
			"attribute vec3 vVertex;"
			"void main(void) "
			"{ gl_Position = mvpMatrix * vec4(vVertex.xyz, 1.0f); "
			"}";

		static const char *szFlatShaderFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"uniform vec4 vColor;"
			"void main(void) "
			"{ gl_FragColor = vColor; "
			"}";

		///////////////////////////////////////////////////////////////////////////////
		// ESS_SHADER_SHADED
		// Point light, diffuse lighting only
		static const char *szShadedVP = "uniform mat4 mvpMatrix;"
			"attribute vec4 vColor;"
			"attribute vec4 vVertex;"
			"varying vec4 vFragColor;"
			"void main(void) {"
			"vFragColor = vColor; "
			" gl_Position = mvpMatrix * vVertex; "
			"}";

		static const char *szShadedFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"varying vec4 vFragColor; "
			"void main(void) { "
			" gl_FragColor = vFragColor; "
			"}";

		// ESS_SHADER_DEFAULT_LIGHT
		// Simple diffuse, directional, and vertex based light
		static const char *szDefaultLightVP = "uniform mat4 mvMatrix;"
			"uniform mat4 pMatrix;"
			"varying vec4 vFragColor;"
			"attribute vec4 vVertex;"
			"attribute vec3 vNormal;"
			"uniform vec4 vColor;"
			"void main(void) { "
			" mat3 mNormalMatrix;"
			" mNormalMatrix[0] = mvMatrix[0].xyz;"
			" mNormalMatrix[1] = mvMatrix[1].xyz;"
			" mNormalMatrix[2] = mvMatrix[2].xyz;"
			" vec3 vNorm = normalize(mNormalMatrix * vNormal);"
			" vec3 vLightDir = vec3(0.0, 0.0, 1.0); "
			" float fDot = max(0.0, dot(vNorm, vLightDir)); "
			" vFragColor.rgb = vColor.rgb * fDot;"
			" vFragColor.a = vColor.a;"
			" mat4 mvpMatrix;"
			" mvpMatrix = pMatrix * mvMatrix;"
			" gl_Position = mvpMatrix * vVertex; "
			"}";


		static const char *szDefaultLightFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"varying vec4 vFragColor; "
			"void main(void) { "
			" gl_FragColor = vFragColor; "
			"}";

		//ESS_SHADER_POINT_LIGHT_DIFF
		// Point light, diffuse lighting only
		static const char *szPointLightDiffVP = "uniform mat4 mvMatrix;"
			"uniform mat4 pMatrix;"
			"uniform vec3 vLightPos;"
			"uniform vec4 vColor;"
			"attribute vec4 vVertex;"
			"attribute vec3 vNormal;"
			"varying vec4 vFragColor;"
			"void main(void) { "
			" mat3 mNormalMatrix;"
			" mNormalMatrix[0] = normalize(mvMatrix[0].xyz);"
			" mNormalMatrix[1] = normalize(mvMatrix[1].xyz);"
			" mNormalMatrix[2] = normalize(mvMatrix[2].xyz);"
			" vec3 vNorm = normalize(mNormalMatrix * vNormal);"
			" vec4 ecPosition;"
			" vec3 ecPosition3;"
			" ecPosition = mvMatrix * vVertex;"
			" ecPosition3 = ecPosition.xyz /ecPosition.w;"
			" vec3 vLightDir = normalize(vLightPos - ecPosition3);"
			" float fDot = max(0.0, dot(vNorm, vLightDir)); "
			" vFragColor.rgb = vColor.rgb * fDot;"
			" vFragColor.a = vColor.a;"
			" mat4 mvpMatrix;"
			" mvpMatrix = pMatrix * mvMatrix;"
			" gl_Position = mvpMatrix * vVertex; "
			"}";


		static const char *szPointLightDiffFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"varying vec4 vFragColor; "
			"void main(void) { "
			" gl_FragColor = vFragColor; "
			"}";

		//ESS_SHADER_TEXTURE_REPLACE
		// Just put the texture on the polygons
		static const char *szTextureReplaceVP = "uniform mat4 mvpMatrix;"
			"attribute vec4 vVertex;"
			"attribute vec2 vTexCoord0;"
			"varying vec2 vTex;"
			"void main(void) "
			"{ vTex = vTexCoord0;"
			" gl_Position = mvpMatrix * vVertex; "
			"}";

		static const char *szTextureReplaceFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"varying vec2 vTex;"
			"uniform sampler2D textureUnit0;"
			"void main(void) "
			"{ gl_FragColor = texture2D(textureUnit0, vTex); "
			"}";


		// Just put the texture on the polygons
		static const char *szTextureRectReplaceVP = "uniform mat4 mvpMatrix;"
			"attribute vec4 vVertex;"
			"attribute vec2 vTexCoord0;"
			"varying vec2 vTex;"
			"void main(void) "
			"{ vTex = vTexCoord0;"
			" gl_Position = mvpMatrix * vVertex; "
			"}";

		static const char *szTextureRectReplaceFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"varying vec2 vTex;"
			"uniform sampler2DRect textureUnit0;"
			"void main(void) "
			"{ gl_FragColor = texture2DRect(textureUnit0, vTex); "
			"}";



		//ESS_SHADER_TEXTURE_MODULATE
		// Just put the texture on the polygons, but multiply by the color (as a unifomr)
		static const char *szTextureModulateVP = "uniform mat4 mvpMatrix;"
			"attribute vec4 vVertex;"
			"attribute vec2 vTexCoord0;"
			"varying vec2 vTex;"
			"void main(void) "
			"{ vTex = vTexCoord0;"
			" gl_Position = mvpMatrix * vVertex; "
			"}";

		static const char *szTextureModulateFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"varying vec2 vTex;"
			"uniform sampler2D textureUnit0;"
			"uniform vec4 vColor;"
			"void main(void) "
			"{ gl_FragColor = vColor * texture2D(textureUnit0, vTex); "
			"}";



		//ESS_SHADER_TEXTURE_POINT_LIGHT_DIFF
		// Point light (Diffuse only), with texture (modulated)
		static const char *szTexturePointLightDiffVP = "uniform mat4 mvMatrix;"
			"uniform mat4 pMatrix;"
			"uniform vec3 vLightPos;"
			"uniform vec4 vColor;"
			"attribute vec4 vVertex;"
			"attribute vec3 vNormal;"
			"varying vec4 vFragColor;"
			"attribute vec2 vTexCoord0;"
			"varying vec2 vTex;"
			"void main(void) { "
			" mat3 mNormalMatrix;"
			" mNormalMatrix[0] = normalize(mvMatrix[0].xyz);"
			" mNormalMatrix[1] = normalize(mvMatrix[1].xyz);"
			" mNormalMatrix[2] = normalize(mvMatrix[2].xyz);"
			" vec3 vNorm = normalize(mNormalMatrix * vNormal);"
			" vec4 ecPosition;"
			" vec3 ecPosition3;"
			" ecPosition = mvMatrix * vVertex;"
			" ecPosition3 = ecPosition.xyz /ecPosition.w;"
			" vec3 vLightDir = normalize(vLightPos - ecPosition3);"
			" float fDot = max(0.0, dot(vNorm, vLightDir)); "
			" vFragColor.rgb = vColor.rgb * fDot;"
			" vFragColor.a = vColor.a;"
			" vTex = vTexCoord0;"
			" mat4 mvpMatrix;"
			" mvpMatrix = pMatrix * mvMatrix;"
			" gl_Position = mvpMatrix * vVertex; "
			"}";


		static const char *szTexturePointLightDiffFP =
#ifdef OPENGL_ES
			"precision mediump float;"
#endif
			"varying vec4 vFragColor;"
			"varying vec2 vTex;"
			"uniform sampler2D textureUnit0;"
			"void main(void) { "
			" gl_FragColor = vFragColor * texture2D(textureUnit0, vTex);"
			"}";


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


		bool COpenGLShaderProgram::AttachSource(const char *shaderSrc, ShaderType shaderType)
		{
			if (shaderType >= 0 && shaderType < ST_COUNT)
			{
				m_pShader[shaderType] = new COpenGLShader();
				m_pShader[shaderType]->CreateBySource(shaderSrc, shaderType);
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
					strncpy(uniform.m_name, name, MAX_FILE_NAME - 1);
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

		void COpenGLShaderProgram::CreateStandShader(E_STAND_SHADER standShader)
		{	
			switch (standShader)
			{
			case mx::render::ESS_SHADER_IDENTITY:
				AttachSource(szIdentityShaderVP, ST_VERTEX);
				AttachSource(szIdentityShaderFP, ST_FRAGMENT);
				BindAttributeLocation(1, VAL_POSITION);
				break;
			case mx::render::ESS_SHADER_FLAT:
				AttachSource(szFlatShaderVP, ST_VERTEX);
				AttachSource(szFlatShaderFP, ST_FRAGMENT);
				BindAttributeLocation(1, VAL_POSITION);
				break;
			case mx::render::ESS_SHADER_SHADED:
				AttachSource(szShadedVP, ST_VERTEX);
				AttachSource(szShadedFP, ST_FRAGMENT);
				BindAttributeLocation(2, VAL_POSITION, VAL_COLOR);
				break;
			case mx::render::ESS_SHADER_DEFAULT_LIGHT:
				AttachSource(szDefaultLightVP, ST_VERTEX);
				AttachSource(szDefaultLightFP, ST_FRAGMENT);
				BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				break;
			case mx::render::ESS_SHADER_POINT_LIGHT_DIFF:
				AttachSource(szPointLightDiffVP, ST_VERTEX);
				AttachSource(szPointLightDiffFP, ST_FRAGMENT);
				BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				break;
			case mx::render::ESS_SHADER_TEXTURE_REPLACE:
				AttachSource(szTextureReplaceVP, ST_VERTEX);
				AttachSource(szTextureReplaceFP, ST_FRAGMENT);
				BindAttributeLocation(2, VAL_POSITION, VAL_TEXTURE0);
				break;
			case mx::render::ESS_SHADER_TEXTURE_MODULATE:
				AttachSource(szTextureModulateVP, ST_VERTEX);
				AttachSource(szTextureModulateFP, ST_FRAGMENT);
				BindAttributeLocation(2, VAL_POSITION, VAL_TEXTURE0);
				break;
			case mx::render::ESS_SHADER_TEXTURE_POINT_LIGHT_DIFF:
				AttachSource(szTexturePointLightDiffVP, ST_VERTEX);
				AttachSource(szTexturePointLightDiffFP, ST_FRAGMENT);
				BindAttributeLocation(3, VAL_POSITION, VAL_NORMAL, VAL_TEXTURE0);
				break;
			case mx::render::ESS_SHADER_TEXTURE_RECT_REPLACE:
				AttachSource(szTextureRectReplaceVP, ST_VERTEX);
				AttachSource(szTextureRectReplaceFP, ST_FRAGMENT);
				BindAttributeLocation(2, VAL_POSITION, VAL_TEXTURE0);
				break;
			default:
				break;
			}

			Link();
		}

	}
}