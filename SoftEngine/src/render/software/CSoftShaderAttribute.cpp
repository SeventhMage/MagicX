#include "CSoftShaderAttribute.h"

namespace se
{
	namespace render
	{
		CSoftShaderAttribute::~CSoftShaderAttribute()
		{			
		}

		ShaderAttrData CSoftShaderAttribute::GetAttribute(base::EVertexAttribute vertType) const
		{
			for (auto it = m_vecAttrData.begin(); it != m_vecAttrData.end(); ++it)
			{
				if (it->vertType == vertType)
				{
					return *it;
				}
			}			
			return ShaderAttrData();
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