#ifndef _MX_CORE_CMATRIX4_H_
#define _MX_CORE_CMATRIX4_H_

#include <assert.h>
#include <string.h>

#include "CVector3.h"
#include "CPlane3.h"

namespace mx
{
	namespace core
	{
		class CMatrix4
		{
		public:
			CMatrix4(){ makeIdentity(); }
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

			inline CMatrix4 &makeIdentity()
			{
				memset(m, 0, sizeof(m));
				m[0] = m[5] = m[10] = m[15] = 1.0f;
				return *this;
			}

			float &operator[](int index)
			{
				return m[index];
			}

			const float &operator[](int index) const
			{
				return m[index];
			}


			inline CMatrix4 operator*(const CMatrix4 &other) const
			{
				return CMatrix4(
					m[0] * other[0] + m[4] * other[1] + m[8] * other[2] + m[12] * other[3],
					m[1] * other[0] + m[5] * other[1] + m[9] * other[2] + m[13] * other[3],
					m[2] * other[0] + m[6] * other[1] + m[10] * other[2] + m[14] * other[3],
					m[3] * other[0] + m[7] * other[1] + m[11] * other[2] + m[15] * other[3],

					m[0] * other[4] + m[4] * other[5] + m[8] * other[6] + m[12] * other[7],
					m[1] * other[4] + m[5] * other[5] + m[9] * other[6] + m[13] * other[7],
					m[2] * other[4] + m[6] * other[5] + m[10] * other[6] + m[14] * other[7],
					m[3] * other[4] + m[7] * other[5] + m[11] * other[6] + m[15] * other[7],

					m[0] * other[8] + m[4] * other[9] + m[8] * other[10] + m[12] * other[11],
					m[1] * other[8] + m[5] * other[9] + m[9] * other[10] + m[13] * other[11],
					m[2] * other[8] + m[6] * other[9] + m[10] * other[10] + m[14] * other[11],
					m[3] * other[8] + m[7] * other[9] + m[11] * other[10] + m[15] * other[11],

					m[0] * other[12] + m[4] * other[13] + m[8] * other[14] + m[12] * other[15],
					m[1] * other[12] + m[5] * other[13] + m[9] * other[14] + m[13] * other[15],
					m[2] * other[12] + m[6] * other[13] + m[10] * other[14] + m[14] * other[15],
					m[3] * other[12] + m[7] * other[13] + m[11] * other[14] + m[15] * other[15]
					);
			}

			CMatrix4 &setTranslation(const CVector3 &translation)
			{
				m[12] = translation.x;
				m[13] = translation.y;
				m[14] = translation.z;
				return *this;
			}

			CMatrix4 &buildProjectionMatrixPerspectiveFovRH(float fieldOfViewRadians, float aspectRatio, float zNear, float zFar)
			{
				const double h = 1.0 / tan(fieldOfViewRadians*0.5);
				assert(aspectRatio != 0.f);
				const float w = static_cast<float>(h / aspectRatio);
				assert(zNear != zFar);

				m[0] = w;
				m[1] = 0;
				m[2] = 0;
				m[3] = 0;

				m[4] = 0;
				m[5] = (float)h;
				m[6] = 0;
				m[7] = 0;

				m[8] = 0;
				m[9] = 0;
				m[10] = (float)((zFar + zNear) / (zNear - zFar));
				m[11] = -1;

				m[12] = 0;
				m[13] = 0;
				m[14] = (float)(2.0f*zNear*zFar / (zNear - zFar));
				m[15] = 0;

				return *this;
			}

			CMatrix4 &buildProjectionMatrixPerspectiveFovLH(float fieldOfViewRadians, float aspectRatio, float zNear, float zFar)
			{
				const double h = 1.0 / tan(fieldOfViewRadians*0.5);
				assert(aspectRatio != 0.f);
				const float w = static_cast<float>(h / aspectRatio);
				assert(zNear != zFar);

				m[0] = w;
				m[1] = 0;
				m[2] = 0;
				m[3] = 0;

				m[4] = 0;
				m[5] = (float)h;
				m[6] = 0;
				m[7] = 0;

				m[8] = 0;
				m[9] = 0;
				m[10] = (float)(zFar / (zFar - zNear));
				m[11] = 1;

				m[12] = 0;
				m[13] = 0;
				m[14] = (float)(-zNear*zFar / (zFar - zNear));
				m[15] = 0;

				return *this;
			}

			CMatrix4 &buildProjectionMatrixOrthoRH(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
			{
				assert(widthOfViewVolume != 0.f);
				assert(heightOfViewVolume != 0.f);
				assert(zNear != zFar);

				m[0] = (float)(2 / widthOfViewVolume);
				m[1] = 0;
				m[2] = 0;
				m[3] = 0;

				m[4] = 0;
				m[5] = (float)(2 / heightOfViewVolume);
				m[6] = 0;
				m[7] = 0;

				m[8] = 0;
				m[9] = 0;
				m[10] = (float)(1 / (zNear - zFar));
				m[11] = 0;

				m[12] = 0;
				m[13] = 0;
				m[14] = (float)(zNear / (zNear - zFar));
				m[15] = 1;

				return *this;
			}

			CMatrix4 &buildProjectionMatrixOrthoLH(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
			{
				assert(widthOfViewVolume != 0.f);
				assert(heightOfViewVolume != 0.f);
				assert(zNear != zFar);

				m[0] = (float)(2 / widthOfViewVolume);
				m[1] = 0;
				m[2] = 0;
				m[3] = 0;

				m[4] = 0;
				m[5] = (float)(2 / heightOfViewVolume);
				m[6] = 0;
				m[7] = 0;

				m[8] = 0;
				m[9] = 0;
				m[10] = (float)(1 / (zFar - zNear));
				m[11] = 0;

				m[12] = 0;
				m[13] = 0;
				m[14] = (float)(zNear / (zNear - zFar));
				m[15] = 1;

				return *this;
			}

			CMatrix4 &buildCameraLookAtMatrix(const CVector3 &position, const CVector3 &dir, const CVector3 &upVector)
			{
				CVector3 zaxis = -dir;
				zaxis.normalize();

				CVector3 xaxis = upVector.crossProduct(zaxis);
				xaxis.normalize();

				CVector3 yaxis = zaxis.crossProduct(xaxis);


				m[0] = (float)xaxis.x;
				m[4] = (float)yaxis.x;
				m[8] = (float)zaxis.x;
				m[12] = (float)-xaxis.dotProduct(position);

				m[1] = (float)xaxis.y;
				m[5] = (float)yaxis.y;
				m[9] = (float)zaxis.y;
				m[13] = (float)-yaxis.dotProduct(position);

				m[2] = (float)xaxis.z;
				m[6] = (float)yaxis.z;
				m[10] = (float)zaxis.z;
				m[14] = -zaxis.dotProduct(position);

				m[3] = 0;// (T)-xaxis.dotProduct(position); //Get the projection at xaxis of position at first, than get negative.
				m[7] = 0;// (T)-yaxis.dotProduct(position);	//The projection at yaxis of position at first, than get negative.
				m[11] = 0;// (T)-zaxis.dotProduct(position);	//The projection at zaxis of position at first, than get negative.
				m[15] = 1;

				return *this;
			}
			CMatrix4 &buildShadowMatrix(const CVector3 &light, const CPlane3 &plane, float point = 1.0f)
			{

			}

			CMatrix4 &setInverseTranslation(const CVector3  &translation)
			{
				m[12] = -translation.x;
				m[13] = -translation.y;
				m[14] = -translation.z;
				return *this;
			}

			CMatrix4 &setRotationRadiansRH(const float rotateX, const float rotateY, const float rotateZ)
			{
				const double cr = cos(rotateX);
				const double sr = sin(rotateX);
				const double cp = cos(rotateY);
				const double sp = sin(rotateY);
				const double cy = cos(rotateZ);
				const double sy = sin(rotateZ);

				m[0] = (float)(cp * cy);
				m[4] = (float)(-cp * sy);
				m[8] = (float)(sp);

				m[1] = (float)(sr * sp * cy + cr * sy);
				m[5] = (float)(-sr * sp * sy + cr * cy);
				m[9] = (float)(-sr * cp);

				m[2] = (float)(-cr * sp * cy + sr * sy);
				m[6] = (float)(cr * sp * sy + sr * cy);
				m[10] = (float)(cr * cp);

				return *this;
			}

			CMatrix4 &setRotationRadiansLH(const float rotateX, const float rotateY, const float rotateZ)
			{
				const double cr = cos(rotateX);
				const double sr = sin(rotateX);
				const double cp = cos(rotateY);
				const double sp = sin(rotateY);
				const double cy = cos(rotateZ);
				const double sy = sin(rotateZ);

				m[0] = (float)(cp * cy);
				m[1] = (float)(cp * sy);
				m[2] = (float)(-sp);

				m[4] = (float)(sr * sp * cy - cr * sy);
				m[5] = (float)(sr * sp * sy + cr * cy);
				m[6] = (float)(sr * cp);

				m[8] = (float)(cr * sp * cy + sr * sy);
				m[9] = (float)(cr * sp * sy - sr * cy);
				m[10] = (float)(cr * cp);

				return *this;
			}

			inline CVector3 getTranslation() const
			{
				return CVector3(m[12], m[13], m[14]);
			}

			inline CMatrix4 &setScale(const CVector3 &scale)
			{
				m[0] = scale.x;
				m[5] = scale.y;
				m[10] = scale.z;
			}

			float m[16];
		};
	}
}

#endif