#include <string.h>

#include "CMesh.h"
#include "CPLXLoader.h"
#include "core/CMatrix4.h"
#include "render/SVertexAttribute.h"
#include "render/SColor.h"

namespace mx
{
	namespace resource
	{
		using namespace render;

		CMesh::CMesh()
			:m_uId(0), m_uState(0), m_uAttr(0), m_fAvgRadius(0), m_fMaxRadius(0), m_uVerticesNum(0), m_pvLocalList(0)
			, m_pvTransList(0), m_uTriangleNum(0), m_pTriangleList(0)
		{
			memset(m_szName, 0, sizeof(m_szName));
		}

		CMesh::~CMesh()
		{
			SAFE_DEL_ARRAY(m_pvLocalList);
			SAFE_DEL_ARRAY(m_pvTransList);
			SAFE_DEL_ARRAY(m_pTriangleList);
		}

		void CMesh::CalculateRadius()
		{
			for (uint i = 0; i < m_uVerticesNum; ++i)
			{
				float length = m_pvLocalList[i].getLengthSQ();
				if (length > m_fMaxRadius)
					m_fMaxRadius = length;
			}
			m_fMaxRadius = sqrt(m_fMaxRadius);
		}

		bool CMesh::Load(const char *filename)
		{
			bool bRet = false;
			const char *extPos = strrchr(filename, '.');
			if (extPos)
			{
				if (0 == strcmp(extPos, ".plg") || 0 == strcmp(extPos, ".plx"))
				{
					CPLXLoader loader;
					loader.LoadResource(filename, this);					
					bRet = true;
				}
			}

			return bRet;
		}

		void CMesh::rotateXZBy(double radians, const CVector3 &center /*= CVector3(0, 1.0f, 0)*/)
		{
			for (uint i = 0; i < m_uVerticesNum; ++i)
			{
				m_pvLocalList[i].rotateXZBy(radians, center);
			}
		}

		void CMesh::rotateXYBy(double radians, const CVector3 &center /*= CVector3(0, 0, 1.0f)*/)
		{
			for (uint i = 0; i < m_uVerticesNum; ++i)
			{
				m_pvLocalList[i].rotateXYBy(radians, center);
			}
		}

		void CMesh::rotateYZBy(double radians, const CVector3 &center /*= CVector3(1.0f, 0, 0)*/)
		{
			for (uint i = 0; i < m_uVerticesNum; ++i)
			{
				m_pvLocalList[i].rotateYZBy(radians, center);
			}
		}
	}
}