#include "CSoftTexture.h"
#include "base/seDef.h"

namespace se
{
	namespace render
	{		

		CSoftTexture::CSoftTexture(int id, ubyte *pData, ulong size, int width, int height)
			:m_id(id)
			, m_size(size)
			, m_width(width)
			, m_height(height)
		{
			m_pData = new ubyte[size];
			memcpy(m_pData, pData, m_size);
		}

		CSoftTexture::~CSoftTexture()
		{
			SAFE_DEL(m_pData);
		}

	}
}