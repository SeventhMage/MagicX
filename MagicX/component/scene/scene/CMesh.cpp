#include "CMesh.h"
#include <string.h>

namespace mx
{
	namespace scene
	{
		CMesh::CMesh(uint vertNum, uint idsNum)
			:m_uVertNum(vertNum)
			, m_uIdsNum(idsNum)			
		{
			m_pVertices = new SVertex[vertNum];
			m_pIndices = new uint[idsNum];
			memset(m_pIndices, 0, sizeof(uint) * idsNum);
		}
	
		CMesh::~CMesh()
		{
			SAFE_DEL(m_pVertices);
			SAFE_DEL(m_pIndices);
		}

	}
}