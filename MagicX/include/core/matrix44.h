#ifndef _MX_MATRIX_44__H_INC_
#define _MX_MATRIX_44__H_INC_

#include <cassert>

#include "mxMath.h"
#include "vector3d.h"
#include "vector2d.h"
#include "plane3d.h"

namespace mx
{
	namespace core
	{

		//	If we use column major. The data used like this:
		//	0	4	8	12
		// 	1	5	9	13
		// 	2	6	10  14
		// 	3	7	11  15
		//
		//	If we use row major. The data used like this:
		//	0	1	2	3
		//	4	5	6	7
		//	8	9	10	11
		//	12	13	14	15
		//
		//	X vector is 0, 1, 2, etc whether we use column major or row major.

		template <typename T>
		class CMatrix44
		{
		public:
			CMatrix44();
			CMatrix44(
				T m00, T m01, T m02, T m03,
				T m10, T m11, T m12, T m13,
				T m20, T m21, T m22, T m23,
				T m30, T m31, T m32, T m33
				);

			T &operator[](int index)
			{
				return m[index];
			}

			const T &operator[](int index) const
			{
				return m[index];
			}

			T &operator()(int row, int col)
			{
				return m[row * 4 + col];
			}

			const T &operator()(int row, int col) const
			{
				return m[row * 4 + col];
			}

			CMatrix44<T> operator+(const CMatrix44<T> &other) const;
			CMatrix44<T> &operator+=(const CMatrix44<T> &other);
			CMatrix44<T> operator-(const CMatrix44<T> &other) const;
			CMatrix44<T> &operator-=(const CMatrix44<T> &other);
			CMatrix44<T> operator*(const CMatrix44<T> &other)const;
			CMatrix44<T> &operator*=(const CMatrix44<T> &other);
			CMatrix44<T> operator*(const T &scalar) const;
			CMatrix44<T> &operator*=(const T &scalar);

			inline CMatrix44<T>& makeIdentity();
			inline bool isIdentity() const;
			inline bool isOrthogonal() const;

			CMatrix44<T> &setTranslation(const vector3d<T> &translation);
			vector3d<T> getTranslation() const;
			CMatrix44<T> &setInverseTranslation(const vector3d<T> & translation);
			inline CMatrix44<T> &setRotationRadians(const T rotateX, const T rotateY, const T rotateZ);
			inline CMatrix44<T> &setRotationDegrees(const T rotateX, const T rotateY, const T rotateZ);
			void getRotationRadians(T &rotateX, T &rotateY, T &rotateZ) const;
			void getRotationDegrees(T &rotateX, T &rotateY, T &rotateZ) const;
			inline CMatrix44<T> &setRotationAxisRadians(const T radians, const vector3d<T> &axis);
			CMatrix44<T> &setScale(const vector3d<T> &scale);
			CMatrix44<T> &setScale(const T scale) { return setScale(vector3d<T>(scale, scale, scale)); }
			vector3d<T> getScale() const;

			vector3d<T> &translate(vector3d<T> &vect) const;
			vector3d<T> &inverseTranslate(vector3d<T> &vect) const;
			vector3d<T> & rotate(vector3d<T> &vect) const;
			vector3d<T> &rotate(vector3d<T> &out, vector3d<T> &in) const;
			vector3d<T> &inverseRotate(vector3d<T> &vect) const;

			vector3d<T> &transform(vector3d<T> &vect) const;
			vector3d<T> &transform(vector3d<T> &out, vector3d<T> &in) const;

			bool makeInverse();
			bool getInverse(CMatrix44<T> &out) const;
			bool getInversePrimitive(CMatrix44<T> &out) const;

			CMatrix44<T> &buildProjectionMatrixPerspectiveFov(float fieldOfViewRadians, float aspectRatio, float zNear, float zFar);
			CMatrix44<T> &buildProjectionMatrixOrtho(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar);
			CMatrix44<T> &buildCameraLookAtMatrix(const vector3df &position, const vector3df &dir, const vector3df &upVector);			
			CMatrix44<T> &buildShadowMatrix(const vector3df &light, const plane3df &plane, float point = 1.0f);

			CMatrix44<T> getTransposed() const;
			inline void getTransposed(CMatrix44<T> &dest) const;

			CMatrix44<T> &buildRotateFromTo(const vector3df &from, const vector3df &to);
			CMatrix44<T> &buildTextureTransform(float rotateRad, const core::vector2df &rotatecenter, const core::vector2df &translate, const core::vector2df &scale);

			T m[16];
		};

		template <typename T>
		CMatrix44<T>::CMatrix44()
		{
			makeIdentity();
		}


		template <typename T>
		CMatrix44<T>::CMatrix44(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33)
		{
			m[0] = m00;
			m[1] = m01;
			m[2] = m02;
			m[3] = m03;

			m[4] = m10;
			m[5] = m11;
			m[6] = m12;
			m[7] = m13;

			m[8] = m20;
			m[9] = m21;
			m[10] = m22;
			m[11] = m23;

			m[12] = m30;
			m[13] = m31;
			m[14] = m32;
			m[15] = m33;
		}


		template <typename T>
		inline CMatrix44<T> CMatrix44<T>::operator+(const CMatrix44<T> &other) const
		{
			return CMatrix44<T>(
				m[0] + other[0], m[1] + other[1], m[2] + other[2], m[3] + other[3],
				m[4] + other[4], m[5] + other[5], m[6] + other[6], m[7] + other[7],
				m[8] + other[8], m[9] + other[9], m[10] + other[10], m[11] + other[11],
				m[12] + other[12], m[13] + other[13], m[14] + other[14], m[15] + other[15]
				);
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::operator+=(const CMatrix44<T> &other)
		{
			for (int i = 0; i < 16; ++i)
				m[i] += other[i];
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> CMatrix44<T>::operator-(const CMatrix44<T> &other) const
		{
			return CMatrix44<T>(
				m[0] - other[0], m[1] - other[1], m[2] - other[2], m[3] - other[3],
				m[4] - other[4], m[5] - other[5], m[6] - other[6], m[7] - other[7],
				m[8] - other[8], m[9] - other[9], m[10] - other[10], m[11] - other[11],
				m[12] - other[12], m[13] - other[13], m[14] - other[14], m[15] - other[15]
				);
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::operator-=(const CMatrix44<T> &other)
		{
			for (int i = 0; i < 16; ++i)
				m[i] -= other[i];
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> CMatrix44<T>::operator*(const CMatrix44<T> &other) const
		{
			return CMatrix44<T>(
				m[0] * other[0] + m[1] * other[4] + m[2] * other[8] + m[3] * other[12],
				m[0] * other[1] + m[1] * other[5] + m[2] * other[9] + m[3] * other[13],
				m[0] * other[2] + m[1] * other[6] + m[2] * other[10] + m[3] * other[14],
				m[0] * other[3] + m[1] * other[7] + m[2] * other[11] + m[3] * other[15],

				m[4] * other[0] + m[5] * other[4] + m[6] * other[8] + m[7] * other[12],
				m[4] * other[1] + m[5] * other[5] + m[6] * other[9] + m[7] * other[13],
				m[4] * other[2] + m[5] * other[6] + m[6] * other[10] + m[7] * other[14],
				m[4] * other[3] + m[5] * other[7] + m[6] * other[11] + m[7] * other[15],

				m[8] * other[0] + m[9] * other[4] + m[10] * other[8] + m[11] * other[12],
				m[8] * other[1] + m[9] * other[5] + m[10] * other[9] + m[11] * other[13],
				m[8] * other[2] + m[9] * other[6] + m[10] * other[10] + m[11] * other[14],
				m[8] * other[3] + m[9] * other[7] + m[10] * other[11] + m[11] * other[15],

				m[12] * other[0] + m[13] * other[4] + m[14] * other[8] + m[15] * other[12],
				m[12] * other[1] + m[13] * other[5] + m[14] * other[9] + m[15] * other[13],
				m[12] * other[2] + m[13] * other[6] + m[14] * other[10] + m[15] * other[14],
				m[12] * other[3] + m[13] * other[7] + m[14] * other[11] + m[15] * other[15]
				);
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::operator*=(const CMatrix44<T> &other)
		{
			m[0] = m[0] * other[0] + m[1] * other[4] + m[2] * other[8] + m[3] * other[12];
			m[1] = m[0] * other[1] + m[1] * other[5] + m[2] * other[9] + m[3] * other[13];
			m[2] = m[0] * other[2] + m[1] * other[6] + m[2] * other[10] + m[3] * other[14];
			m[3] = m[0] * other[3] + m[1] * other[7] + m[2] * other[11] + m[3] * other[15];

			m[4] = m[4] * other[0] + m[5] * other[4] + m[6] * other[8] + m[7] * other[12];
			m[5] = m[4] * other[1] + m[5] * other[5] + m[6] * other[9] + m[7] * other[13];
			m[6] = m[4] * other[2] + m[5] * other[6] + m[6] * other[10] + m[7] * other[14];
			m[7] = m[4] * other[3] + m[5] * other[7] + m[6] * other[11] + m[7] * other[15];

			m[8] = m[8] * other[0] + m[9] * other[4] + m[10] * other[8] + m[11] * other[12];
			m[9] = m[8] * other[1] + m[8] * other[5] + m[10] * other[9] + m[11] * other[13];
			m[10] = m[8] * other[2] + m[9] * other[6] + m[10] * other[10] + m[11] * other[14];
			m[11] = m[8] * other[3] + m[9] * other[7] + m[10] * other[11] + m[11] * other[15];

			m[12] = m[12] * other[0] + m[13] * other[4] + m[14] * other[8] + m[15] * other[12];
			m[13] = m[12] * other[1] + m[13] * other[5] + m[14] * other[9] + m[15] * other[13];
			m[14] = m[12] * other[2] + m[13] * other[6] + m[14] * other[10] + m[15] * other[14];
			m[15] = m[12] * other[3] + m[13] * other[7] + m[14] * other[11] + m[15] * other[15];
		}

		template <typename T>
		inline CMatrix44<T> CMatrix44<T>::operator*(const T &scalar) const
		{
			return CMatrix44<T>(
				m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar,
				m[4] * scalar, m[5] * scalar, m[6] * scalar, m[7] * scalar,
				m[8] * scalar, m[9] * scalar, m[10] * scalar, m[11] * scalar,
				m[12] * scalar, m[13] * scalar, m[14] * scalar, m[15] * scalar
				);
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::operator*=(const T &scalar)
		{
			for (int i = 0; i < 16; ++i)
			{
				m[i] *= scalar;
			}
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::makeIdentity()
		{
			memset(m, 0, sizeof(m));
			m[0] = m[5] = m[10] = m[15] = static_cast<T>(1);
			return *this;
		}

		template <typename T>
		inline bool CMatrix44<T>::isIdentity() const
		{
			if (core::equals(m[0], (T)1) && core::equals(m[1], (T)0) && core::equals(m[2], (T)0) && core::equals(m[3], (T)0)
				&& core::equals(m[4], (T)0) && core::equals(m[5], (T)1) && core::equals(m[6], (T)0) && core::equals(m[7], (T)0)
				&& core::equals(m[8], (T)0) && core::equals(m[9], (T)0) && core::equals(m[10], (T)1) && core::equals(m[11], (T)0)
				&& core::equals(m[12], (T)0) && core::equals(m[13], (T)0) && core::equals(m[14], (T)0) && core::equals(m[15], (T)1)
				)
				return true;
			return false;
		}

		template <typename T>
		inline bool CMatrix44<T>::isOrthogonal() const
		{
			if (core::equals(m[0], (T)1) && core::equals(m[5], (T)1) && core::equals(m[10], (T)1) && core::equals(m[15], (T)1))
			{
				if (core::iszero(m[0] * [4] + m[1] * [5] + m[2] * m[6] + m[3] * m[7]) && core::iszero(m[0] * [8] + m[1] * [9] + m[2] * m[10] + m[3] * m[11])
					&& core::iszero(m[0] * [12] + m[1] * [13] + m[2] * m[14] + m[3] * m[15]) && core::iszero(m[4] * [8] + m[5] * [9] + m[6] * m[10] + m[7] * m[11])
					&& core::iszero(m[4] * [12] + m[5] * [13] + m[6] * m[14] + m[7] * m[15]) && core::iszero(m[8] * m[12] + m[9] * m[13] + m[10] * m[14] + m[11] * m[15])
					)
					return true;
			}
			return false;
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::setTranslation(const vector3d<T> &translation)
		{
			m[3] = translation.x;
			m[7] = translation.y;
			m[11] = translation.z;
			return *this;
		}

		template <typename T>
		inline vector3d<T> CMatrix44<T>::getTranslation() const
		{
			return vector3d<T>(m[3], m[7], m[11]);
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::setInverseTranslation(const vector3d<T> & translation)
		{
			m[3] = -translation.x;
			m[7] = -translation.y;
			m[11] = -translation.z;
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::setRotationRadians(const T rotateX, const T rotateY, const T rotateZ)
		{
			const double cr = (T)cos(rotateX);
			const double sr = (T)sin(rotateX);
			const double cp = (T)cos(rotateY);
			const double sp = (T)sin(rotateY);
			const double cy = (T)cos(rotateZ);
			const double sy = (T)sin(rotateZ);

#ifdef MX_LEFT_HANDED_COORDINATE_SYSTEM
			m[0] = (T)(cp * cy);
			m[1] = (T)(cp * sy);
			m[2] = (T)(-sp);

			m[4] = (T)(sr * sp * cy - cr * sy);
			m[5] = (T)(sr * sp * sy + cr * cy);
			m[6] = (T)(sr * cp);

			m[8] = (T)(cr * sp * cy + sr * sy);
			m[9] = (T)(cr * sp * sy - sr * cy);
			m[10] = (T)(cr * cp);
#else
			m[0] = (T)(cp * cy);
			m[4] = (T)(-cp * sy);
			m[8] = (T)(sp);

			m[1] = (T)(sr * sp * cy + cr * sy);
			m[5] = (T)(-sr * sp * sy + cr * cy);
			m[9] = (T)(-sr * cp);

			m[2] = (T)(-cr * sp * cy + sr * sy);
			m[6] = (T)(cr * sp * sy + sr * cy);
			m[10] = (T)(cr * cp);
#endif
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::setRotationDegrees(const T rotateX, const T rotateY, const T rotateZ)
		{
			return setRotationRadians(DEG_TO_RAD(rotateX), DEG_TO_RAD(rotateY), DEG_TO_RAD(rotateZ));
		}

		template <typename T>
		inline void CMatrix44<T>::getRotationRadians(T &rotateX, T &rotateY, T &rotateZ) const
		{

		}

		template <typename T>
		inline void CMatrix44<T>::getRotationDegrees(T &rotateX, T &rotateY, T &rotateZ) const
		{

		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::setRotationAxisRadians(const T radians, const vector3d<T> &axis)
		{

		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::setScale(const vector3d<T> &scale)
		{
			m[0] = scale.x;
			m[5] = scale.y;
			m[10] = scale.z;
		}

		template <typename T>
		inline vector3d<T> CMatrix44<T>::getScale() const
		{
			if (core::iszero(m[1]) && core::iszero(m[2]) &&
				core::iszero(m[4]) && core::iszero(m[6]) &&
				core::iszero(m[8]) && core::iszero(m[9]))
				return vector3d<T>(m[0], m[5], m[10]);

			return vector3d<T>((T)sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]),
				(T)sqrt(m[4] * m[4] + m[5] * m[5] + m[6] * m[6]),
				(T)sqrt(m[8] * m[8] + m[9] * m[9] + m[10] * m[10]));
		}

		template <typename T>
		inline vector3d<T> &CMatrix44<T>::translate(vector3d<T> &vect) const
		{
			vect.x += m[3];
			vect.y += m[7];
			vect.z += m[11];
			return vect;
		}

		template <typename T>
		inline vector3d<T> &CMatrix44<T>::inverseTranslate(vector3d<T> &vect) const
		{
			vect.x -= m[3];
			vect.y -= m[7];
			vect.z -= m[11];
			return vect;
		}

		template <typename T>
		inline vector3d<T> &CMatrix44<T>::rotate(vector3d<T> &vect) const
		{
			T temp[3];
		
			temp[0] = m[0] * vect.x + m[1] * vect.y + m[2] * vect.z;
			temp[1] = m[4] * vect.x + m[5] * vect.y + m[6] * vect.z;
			temp[2] = m[8] * vect.x + m[9] * vect.y + m[10] * vect.z;

			vect.x = temp[0];
			vect.y = temp[1];
			vect.z = temp[2];

			return vect;
		}

		template <typename T>
		inline vector3d<T> &CMatrix44<T>::rotate(vector3d<T> &out, vector3d<T> &in) const
		{
			out.x = m[0] * in.x + m[1] * in.y + m[2] * in.z;
			out.y = m[4] * in.x + m[5] * in.y + m[6] * in.z;
			out.z = m[8] * in.x + m[9] * in.y + m[10] * in.z;
		}

		template <typename T>
		inline vector3d<T> &CMatrix44<T>::inverseRotate(vector3d<T> &vect) const
		{			
			T temp[3];

			temp[0] = m[0] * vect.x + m[4] * vect.y + m[8] * vect.z;
			temp[1] = m[1] * vect.x + m[5] * vect.y + m[9] * vect.z;
			temp[2] = m[2] * vect.x + m[6] * vect.y + m[10] * vect.z;

			vect.x = temp[0];
			vect.y = temp[1];
			vect.z = temp[2];

			return vect;
		}

		template <typename T>
		inline vector3d<T> &CMatrix44<T>::transform(vector3d<T> &vect) const
		{
			T temp[3];

			temp[0] = m[0] * vect.x + m[1] * vect.y + m[2] * vect.z + m[3];
			temp[1] = m[4] * vect.x + m[5] * vect.y + m[6] * vect.z + m[7];
			temp[2] = m[8] * vect.x + m[9] * vect.y + m[10] * vect.z + m[11];

			vect.x = temp[0];
			vect.y = temp[1];
			vect.z = temp[2];

			return vect;
		}

		template <typename T>
		inline vector3d<T> &CMatrix44<T>::transform(vector3d<T> &out, vector3d<T> &in) const
		{
			out.x = m[0] * in.x + m[1] * in.y + m[2] * in.z + m[3];
			out.y = m[4] * in.x + m[5] * in.y + m[6] * in.z + m[7];
			out.z = m[8] * in.x + m[9] * in.y + m[10] * in.z + m[11];

			return out;
		}

		template <typename T>
		inline bool CMatrix44<T>::makeInverse()
		{
			CMatrix44<T> temp;
			if (getInverse(temp))
			{
				*this = temp;
			}
			return false;
		}

		template <typename T>
		inline bool CMatrix44<T>::getInverse(CMatrix44<T> &out) const
		{

		}

		template <typename T>
		inline bool CMatrix44<T>::getInversePrimitive(CMatrix44<T> &out) const
		{

		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::buildProjectionMatrixPerspectiveFov(float fieldOfViewRadians, float aspectRatio, float zNear, float zFar)
		{
			const double h = 1.0 / tan(fieldOfViewRadians*0.5);
			assert(aspectRatio != 0.f);
			const T w = static_cast<T>(h / aspectRatio);
			assert(zNear != zFar);

#ifdef MX_LEFT_HANDED_COORDINATE_SYSTEM
			m[0] = w;
			m[1] = 0;
			m[2] = 0;
			m[3] = 0;

			m[4] = 0;
			m[5] = (T)h;
			m[6] = 0;
			m[7] = 0;

			m[8] = 0;
			m[9] = 0;
			m[10] = (T)(zFar / (zFar - zNear));
			m[11] = 1;

			m[12] = 0;
			m[13] = 0;
			m[14] = (T)(-zNear*zFar / (zFar - zNear));
			m[15] = 0;
#else
			m[0] = w;
			m[4] = 0;
			m[8] = 0;
			m[12] = 0;

			m[1] = 0;
			m[5] = (T)h;
			m[9] = 0;
			m[13] = 0;

			m[2] = 0;
			m[6] = 0;
			m[10] = (T)(zFar+zNear/(zNear-zFar));
			m[14] = -1;

			m[3] = 0;
			m[7] = 0;
			m[11] = (T)(2.0f*zNear*zFar/(zNear-zFar));
			m[15] = 0;
#endif
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::buildProjectionMatrixOrtho(float widthOfViewVolume, float heightOfViewVolume, float zNear, float zFar)
		{
			assert(widthOfViewVolume != 0.f);
			assert(heightOfViewVolume != 0.f);
			assert(zNear != zFar);

#ifdef MX_LEFT_HANDED_COORDINATE_SYSTEM
			m[0] = (T)(2 / widthOfViewVolume);
			m[1] = 0;
			m[2] = 0;
			m[3] = 0;

			m[4] = 0;
			m[5] = (T)(2 / heightOfViewVolume);
			m[6] = 0;
			m[7] = 0;

			m[8] = 0;
			m[9] = 0;
			m[10] = (T)(1 / (zFar - zNear));
			m[11] = 0;

			m[12] = 0;
			m[13] = 0;
			m[14] = (T)(zNear / (zNear - zFar));
			m[15] = 1;
#else

			m[0] = (T)(2 / widthOfViewVolume);
			m[1] = 0;
			m[2] = 0;
			m[3] = 0;

			m[4] = 0;
			m[5] = (T)(2 / heightOfViewVolume);
			m[6] = 0;
			m[7] = 0;

			m[8] = 0;
			m[9] = 0;
			m[10] = (T)(1 / (zNear - zFar));
			m[11] = 0;

			m[12] = 0;
			m[13] = 0;
			m[14] = (T)(zNear / (zNear - zFar));
			m[15] = 1;
#endif
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::buildCameraLookAtMatrix(const vector3df &position, const vector3df &dir, const vector3df &upVector)
		{
			vector3df zaxis = -dir;
			zaxis.normalize();

			vector3df xaxis = upVector.crossProduct(zaxis);
			xaxis.normalize();

			vector3df yaxis = zaxis.crossProduct(xaxis);


			m[0] = (T)xaxis.x;
			m[1] = (T)yaxis.x;
			m[2] = (T)zaxis.x;
			m[3] = (T)-xaxis.dotProduct(position);;

			m[4] = (T)xaxis.y;
			m[5] = (T)yaxis.y;
			m[6] = (T)zaxis.y;
			m[7] = (T)-yaxis.dotProduct(position);

			m[8] = (T)xaxis.z;
			m[9] = (T)yaxis.z;
			m[10] = (T)zaxis.z;
			m[11] = (T)-zaxis.dotProduct(position);
			
			m[12] = 0;// (T)-xaxis.dotProduct(position); //Get the projection at xaxis of position at first, than get negative.
			m[13] = 0;// (T)-yaxis.dotProduct(position);	//The projection at yaxis of position at first, than get negative.
			m[14] = 0;// (T)-zaxis.dotProduct(position);	//The projection at zaxis of position at first, than get negative.
			m[15] = 1;

			return *this;
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::buildShadowMatrix(const vector3df &light, const plane3df &plane, float point = 1.0f)
		{
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> CMatrix44<T>::getTransposed() const
		{
			CMatrix44<T> temp;
			getTransposed(temp);
			return temp;
		}

		template <typename T>
		inline void CMatrix44<T>::getTransposed(CMatrix44<T> &dest) const
		{
			dest[0] = m[0];
			dest[1] = m[4];
			dest[2] = m[8];
			dest[3] = m[12];

			dest[4] = m[1];
			dest[5] = m[5];
			dest[6] = m[9];
			dest[7] = m[13];

			dest[8] = m[2];
			dest[9] = m[6];
			dest[10] = m[10];
			dest[11] = m[14];

			dest[12] = m[3];
			dest[13] = m[7];
			dest[14] = m[11];
			dest[15] = m[15];
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::buildRotateFromTo(const vector3df &from, const vector3df &to)
		{
			return *this;
		}

		template <typename T>
		inline CMatrix44<T> &CMatrix44<T>::buildTextureTransform(float rotateRad, const core::vector2df &rotatecenter, const core::vector2df &translate, const core::vector2df &scale)
		{
			return *this;
		}		
	}
}

#endif // !_MX_MATRIX_44__H_INC_
