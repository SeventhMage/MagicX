/************************************************************************/
/* 虚拟跟踪球，用于物体旋转												*/
/************************************************************************/

#ifndef _MX_BASE_C_VIRTUAL_TRACE_BALL_H_
#define _MX_BASE_C_VIRTUAL_TRACE_BALL_H_

#include "math/CVector3.h"
#include "math/CMatrix4.h"

namespace mx
{
	namespace base
	{
		class CVirtualTraceBall
		{
		public:
			CVirtualTraceBall(float fRadius);
			~CVirtualTraceBall();

			math::CVector3 GetSphereCoord(float fScreenX, float fScreenY);
			math::CMatrix4 GetRotateMatrix(float fCurScnX, float fCurScnY, float fLastCurScnX, float fLastCurScnY);
		private:
			float m_fRadius;
		};
	}
}

#endif