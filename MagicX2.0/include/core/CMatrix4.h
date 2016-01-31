#ifndef _MX_CORE_CMATRIX4_H_
#define _MX_CORE_CMATRIX4_H_

namespace mx
{
	namespace core
	{
		class CMatrix4
		{
		public:
			CMatrix4(){}
			CMatrix4(float m11, float m12, float m13, float m14, 
					float m21, float m22, float m23, float m24,
					float m31, float m32, float m33, float m34,
					float m41, float m42, float m43, float m44
					)
			{
				m[0] = m11, m[1] = m12, m[2] = m13, m[3] = m14;
				m[4] = m21, m[5] = m22, m[6] = m23, m[7] = m24;
				m[8] = m31, m[9] = m32, m[10] = m33, m[11] = m34;
				m[12] = m41, m[13] = m42, m[14] = m43, m[15] = m44;
			}
			CMatrix4(float m[16])
			{
				for (int i = 0; i < 16; ++i)
				{
					this->m[i] = m[i];
				}
			}

			float m[16];
		};
	}
}

#endif