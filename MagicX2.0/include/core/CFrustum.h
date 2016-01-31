#ifndef _MX_CORE_CFRUSTUM_H_
#define _MX_CORE_CFRUSTUM_H_

#include "CPlane3.h"

namespace mx
{
	namespace core
	{
		class CFrustum
		{
		public:
			CFrustum(){};
			~CFrustum(){};

			CPlane3 m_NearClip;
			CPlane3 m_farClip;
			CPlane3 m_leftClip;
			CPlane3 m_rightClip;
			CPlane3 m_topClip;
			CPlane3 m_bottomClip;
		};
	}
}

#endif