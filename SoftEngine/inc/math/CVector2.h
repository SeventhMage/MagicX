#ifndef _MX_CORE_CVECTOR2_H_
#define _MX_CORE_CVECTOR2_H_

namespace se
{
	namespace math
	{
		class CVector2
		{
		public:
			CVector2(float x, float y) :x(x), y(y){}
			CVector2() :x(0), y(0){}

			float getLength() const { return static_cast<float>(sqrt(x * x + y * y)); }
			float getDistanceFrom(const CVector2 &other) const
			{
				return CVector2(x - other.x, y - other.y).getLength();
			}

			CVector2 operator*(const float v) const { return CVector2(x * v, y * v); }

			union
			{
				float v[2];
				struct
				{
					float x, y;
				};
			};

		};
	}
}

#endif