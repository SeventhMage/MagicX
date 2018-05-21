#include "base/CAABBox.h"

namespace mx
{
	CAABBox::CAABBox()
	{
		m_vecMin[0] = m_vecMin[1] = m_vecMin[2] = 0;
		m_vecMax[0] = m_vecMax[1] = m_vecMax[2] = 0;
	}

	CAABBox::CAABBox(const point3 &p1, const point3 &p2)
	{
		m_vecMin[0] = MIN(p1[0], p2[0]);
		m_vecMin[1] = MIN(p1[1], p2[1]);
		m_vecMin[2] = MIN(p1[2], p2[2]);

		m_vecMax[0] = MAX(p1[0], p2[0]);
		m_vecMax[1] = MAX(p1[1], p2[1]);
		m_vecMax[2] = MAX(p1[2], p2[2]);
	}

	CAABBox CAABBox::Union(const CAABBox &b, const point3 &p)
	{
		CAABBox ret = b;
		ret.m_vecMin[0] = MIN(b.m_vecMin[0], p[0]);
		ret.m_vecMin[1] = MIN(b.m_vecMin[1], p[1]);
		ret.m_vecMin[2] = MIN(b.m_vecMin[2], p[2]);
		ret.m_vecMax[0] = MIN(b.m_vecMax[0], p[0]);
		ret.m_vecMax[1] = MIN(b.m_vecMax[1], p[1]);
		ret.m_vecMax[2] = MIN(b.m_vecMax[2], p[2]);
	}

	void CAABBox::Union(const point3 &p)
	{
		m_vecMin[0] = MIN(m_vecMin[0], p[0]);
		m_vecMin[1] = MIN(m_vecMin[1], p[1]);
		m_vecMin[2] = MIN(m_vecMin[2], p[2]);
		m_vecMax[0] = MIN(m_vecMax[0], p[0]);
		m_vecMax[1] = MIN(m_vecMax[1], p[1]);
		m_vecMax[2] = MIN(m_vecMax[2], p[2]);
	}

	CAABBox::~CAABBox()
	{

	}

}