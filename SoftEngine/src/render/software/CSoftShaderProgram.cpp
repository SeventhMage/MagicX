#include "CSoftShaderProgram.h"

namespace se
{
	namespace render
	{

		CSoftShaderProgram::CSoftShaderProgram()
		{

		}

		CSoftShaderProgram::~CSoftShaderProgram()
		{

		}

		void CSoftShaderProgram::SetUniform(EUniformName uniformName, ubyte *data, uint size)
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
				case se::render::UN_MODEL_MAT:					
				case se::render::UN_WORLD_MAT:					
				case se::render::UN_VIEW_MAT:					
				case se::render::UN_PROJ_MAT:
					uniform.name = uniformName;
					uniform.data = new float[size];
					memcpy(uniform.data, data, size);
					m_uniformMap[uniform.name] = uniform;
					break;
				default:
					break;
				}
			}

		}

		float * CSoftShaderProgram::GetUniform(EUniformName uniformName)
		{
			auto it = m_uniformMap.find(uniformName);
			if (it != m_uniformMap.end())
				return it->second.data;
			return nullptr;
		}

	}
}