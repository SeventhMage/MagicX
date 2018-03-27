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

				switch (uniformName)
				{								
				case se::render::UN_WORLD_MAT:					
				case se::render::UN_VIEW_MAT:					
				case se::render::UN_PROJ_MAT:
					uniform.name = uniformName;		
					uniform.data = new byte[size];
					uniform.type = type;
					uniform.size = size;

					memcpy(uniform.data, data, size);
					m_uniformMap[uniform.name] = uniform;
					break;
				default:
					break;
				}
			}

		}

		byte * CSoftShaderProgram::GetUniform(EUniformName uniformName)
		{
			auto it = m_uniformMap.find(uniformName);
			if (it != m_uniformMap.end())
				return it->second.data;
			return nullptr;
		}

	}
}