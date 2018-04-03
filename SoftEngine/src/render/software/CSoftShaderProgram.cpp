#include "CSoftShaderProgram.h"

namespace se
{
	namespace render
	{

		CSoftShaderProgram::CSoftShaderProgram(uint id)
			:m_id(id)
			, m_pVertexShader(new CSoftVertexShader())
			, m_pFragShader(new CSoftFragmentShader())			
		{			
			
		}

		CSoftShaderProgram::~CSoftShaderProgram()
		{
			for (auto it = m_uniformMap.begin(); it != m_uniformMap.end(); ++it)
			{
				delete[]it->second.data;
			}
			m_uniformMap.clear();
		}

		void CSoftShaderProgram::SetUniform(EUniformName uniformName, const void *data, EDataType type, uint size)
		{
			auto it = m_uniformMap.find(uniformName);
			if (it != m_uniformMap.end())
			{
				memcpy(it->second.data, data, size);
			}
			else
			{
				Uniform uniform;
				uniform.name = uniformName;
				uniform.data = new ubyte[size];
				uniform.type = type;
				uniform.size = size;

				memcpy(uniform.data, data, size);
				m_uniformMap[uniform.name] = uniform;			
			}

		}

		ubyte * CSoftShaderProgram::GetUniform(EUniformName uniformName)
		{
			auto it = m_uniformMap.find(uniformName);
			if (it != m_uniformMap.end())
				return it->second.data;
			return nullptr;
		}

		void CSoftShaderProgram::SetIllumination(CIllumination *pIllumination)
		{
			if (m_pVertexShader)
				m_pVertexShader->SetIllumination(pIllumination);
		}

	}
}