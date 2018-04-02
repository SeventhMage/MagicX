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

		void CSoftShaderAttribute::SetAttribute(base::EVertexAttribute vertType, const void *source, uint size)
		{
			ShaderAttrData attrData(vertType, source, size);
			bool bHaveAttr = false;
			for (auto it = m_vecAttrData.begin(); it != m_vecAttrData.end(); ++it)
			{
				if (it->vertType == vertType)
				{
					*it = attrData;
					bHaveAttr = true;
					break;
				}
			}

			if (!bHaveAttr)
			{
				m_vecAttrData.push_back(attrData);
			}
		}

		void CSoftShaderAttribute::Clear()
		{
			m_vecAttrData.clear();
		}

	}
}