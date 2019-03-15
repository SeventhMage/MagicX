#include "SUniform.h"

#include <string.h>

namespace mx
{
	namespace render
	{
		SUniform::SUniform(const char *name)
			: m_format(UF_UNKNOWN)
			, m_count(0)
			, m_size(0)
			, m_value(nullptr)
		{
			strncpy(m_name, name, sizeof(m_name));
		}

		SUniform::~SUniform()
		{
			SAFE_DEL(m_value);
		}

		void SUniform::SetValue(const void *value, uint size)
		{
			if (value && size > 0)
			{
				if (!m_value || size != m_size)
				{
					m_size = size;
					SAFE_DEL(m_value);
					m_value = new byte[m_size];
				}
				memcpy(m_value, value, m_size);
			}
		}
	}
}