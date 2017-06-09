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