#ifndef _MX_RENDER_C_SHADER_PROGRAM_H_
#define _MX_RENDER_C_SHADER_PROGRAM_H_

#include "CShaderProgram.h"

namespace mx
{
	namespace render
	{


		CShaderProgram::CShaderProgram()
		{

		}

		CShaderProgram::~CShaderProgram()
		{

		}

		void CShaderProgram::SetUniform(const char *name, void *value)
		{
			int location = GetUniformLocation(name);
			if (location >= 0)
			{
				SetUniform(location, value);
			}
		}

		void CShaderProgram::SetUniform(int location, void *value)
		{
			if (m_uniforms.find(location) != m_uniforms.end())
				m_uniforms[location].SetValue(value);
		}

		int CShaderProgram::GetUniformLocation(const char *name) const
		{
			UniformArray::const_iterator cit = m_uniforms.begin();
			for (; cit != m_uniforms.end(); ++cit)
			{
				if (cit->second.m_name == name)
				{
					return cit->second.m_location;
				}
			}
			return -1;
		}

	}
}

#endif