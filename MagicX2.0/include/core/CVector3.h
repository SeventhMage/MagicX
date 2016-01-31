#ifndef _MX_CORE_CVECTOR3_H_
#define _MX_CORE_CVECTOR3_H_


namespace mx
{
	namespace core
	{
		class CVector3
		{
		public:
			CVector3():x(0), y(0), z(0) {}
			CVector3(float x, float y, float z) :x(x), y(y), z(z){}

			union
			{
				float v[3];
				struct  
				{
					float x, y, z;
				};
			};
		};
	}
}

#endif