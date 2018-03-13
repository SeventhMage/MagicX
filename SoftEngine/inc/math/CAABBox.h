#ifndef _SE_MATH_CAABBOX_H_
#define _SE_MATH_CAABBOX_H_

#include "CVector3.h"

namespace se
{
	namespace math
	{		
		class CAABBox
		{
		public:
			CAABBox():m_minEdge(-1, -1, -1), m_maxEdge(1, 1, 1){}
			CAABBox(const CVector3 &minEdge, const CVector3 &maxEdge) :m_minEdge(minEdge), m_maxEdge(maxEdge){}			

			CVector3 m_minEdge;
			CVector3 m_maxEdge;
		};
	}
}

#endif
