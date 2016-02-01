#include "CMesh.h"
#include <string.h>


namespace mx
{
	namespace resource
	{

		CMesh::CMesh()
			:m_uId(0), m_uState(0), m_uAttr(0), m_fAvgRadius(0), m_fMaxRadius(0), m_uVerticesNum(0), m_pvLocalList(0)
			, m_pvTransList(0), m_uTriangleNum(0), m_pTriangleList(0)
		{
			memset(m_szName, 0, sizeof(m_szName));
		}

		CMesh::~CMesh()
		{

		}

		void CMesh::CalculateBoundingBox()
		{

		}

		void CMesh::CalculateRadius()
		{

		}

		byte * CMesh::GetVerticesData() const
		{
			return 0;
		}

		mx::uint CMesh::GetVerticesSize() const
		{
			return 0;
		}

		mx::uint CMesh::GetVerticesCount() const
		{
			return 0;
		}

		mx::uint CMesh::GetVertexStride() const
		{
			return 0;
		}

		byte * CMesh::GetIndicesData() const
		{
			return 0;
		}

		mx::uint CMesh::GetIndicesSize() const
		{
			return 0;
		}

		mx::uint CMesh::GetIndicesCount() const
		{
			return 0;
		}

	}
}