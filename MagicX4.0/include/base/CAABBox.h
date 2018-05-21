#ifndef _BASE_C_AABBOX_H_
#define _BASE_C_AABBOX_H_

#include "vector.h"

namespace mx
{
	class CAABBox
	{
	public:
		CAABBox();
		CAABBox(const point3 &p1, const point3 &p2);
		~CAABBox();
		static CAABBox Union(const CAABBox &b, const point3 &p);
		void Union(const point3 &p);
		static CAABBox Union(const CAABBox &b1, const CAABBox &b2);
		void Union(const CAABBox &b);
		bool Overlaps(const CAABBox &b) const;
		bool Inside(const point3 &p) const;

	private:
		vec3 m_vecMin;
		vec3 m_vecMax;
	};
}

#endif