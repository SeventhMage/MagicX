#include "CSoftShaderAttribute.h"

namespace se
{
	namespace render
	{
		const ShaderAttrData & CSoftShaderAttribute::GetAttribute(base::EVertexAttribute vertType)
		{
			for (auto data : m_vecAttrData)
			{
				if (data.vertType == vertType)
				{
					return data;
				}
			}
		}

		void CSoftShaderAttribute::SetAttribute(base::EVertexAttribute vertType, void *source, uint size)
		{
			ShaderAttrData attrData(vertType, source, size);
			bool bHaveAttr = false;
			for (auto data : m_vecAttrData)
			{
				if (data.vertType == vertType)
				{
					data = attrData;
					bHaveAttr = true;
					break;
				}
			}

			if (!bHaveAttr)
			{
				m_vecAttrData.push_back(attrData);
			}
		}

	}
}