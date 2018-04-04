#ifndef _MX_CORE_CVECTOR4_H_
#define _MX_CORE_CVECTOR4_H_

#include "CVector3.h"

namespace se
{
	namespace math
	{
		class CVector4
		{
		public:
			CVector4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w){}
			CVector4() :x(0), y(0){}

			inline float getDistanceFrom(const CVector4 &other) const
			{
				return CVector3(x - other.x, y - other.y, z - other.z).getLength();
			}

			inline float getInvDistanceFrom(const CVector4 &other) const
			{
				return base::InvSqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));				
			}
			union
			{
				float v[4];
				struct
				{
					float x, y, z, w;
				};
			};

		};
	}
}

#endif