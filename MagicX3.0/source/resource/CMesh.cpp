#include "CMesh.h"

#include <string.h>

namespace mx
{
	namespace resource
	{


		CMesh::CMesh(int triNum)			
			: m_totalTris(triNum)
			, m_curTriNum(0)
		{
			m_triangles = new Triangle[triNum];			
		}

		CMesh::~CMesh()
		{
			if (m_triangles)
				delete[]m_triangles;
		}

		bool CMesh::HaveIndex()
		{

		}

		mx::resource::PTriangle CMesh::GetMesh()
		{
			return m_triangles;
		}

		int CMesh::GetStride()
		{

		}

		void CMesh::AddTriangle(const Triangle &tri)
		{
			if (m_curTriNum < m_totalTris)
				m_triangles[m_curTriNum++] = tri;
		}

		void CMesh::Clear()
		{
			m_curTriNum = 0;
		}

	}
}