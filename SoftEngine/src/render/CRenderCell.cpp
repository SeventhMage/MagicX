#include "CRenderCell.h"
#include "CSoftEngine.h"

namespace se
{
	namespace render
	{

		CRenderCell::CRenderCell(uint bufferId, uint materialId, uint textureId)
			:m_bufferId(bufferId)
			, m_textureId(textureId)
			, m_materialId(materialId)
			, m_pParentQueue(nullptr)
		{
			
		}

		CRenderCell::~CRenderCell()
		{
			for (auto it = m_mapShaderParam.begin(); it != m_mapShaderParam.end(); ++it)
			{
				delete[]it->second.data;
			}
			m_mapShaderParam.clear();
			
		}

		void CRenderCell::SetRenderQueue(IRenderQueue *parent)
		{
			m_pParentQueue = parent;
		}

		void CRenderCell::SetShaderParam(EUniformName name, void *data, EDataType type, uint size)
		{
			auto it = m_mapShaderParam.find(name);
			if (it != m_mapShaderParam.end())
			{
				memcpy(it->second.data, data, size);
			}
			else
			{
				ShaderParam param;
				switch (name)
				{
				case se::render::UN_WORLD_MAT:
					param.name = name;
					param.data = new byte[size];
					param.type = type;
					param.size = size;
					memcpy(param.data, data, size);
					m_mapShaderParam[param.name] = param;
					break;
				default:
					break;
				}
			}
		}

		void CRenderCell::BindShaderParams(IShaderProgram *pShaderParam)
		{
			for (auto it = m_mapShaderParam.begin(); it != m_mapShaderParam.end(); ++it)
			{
				pShaderParam->SetUniform(it->first, it->second.data, it->second.type, it->second.size);
			}
		}
}
}