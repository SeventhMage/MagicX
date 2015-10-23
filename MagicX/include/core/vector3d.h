#ifndef _MX_VECTOR_3D_H_INC_
#define _MX_VECTOR_3D_H_INC_

#include "../common/mxMath.h"

namespace mx
{
	namespace core
	{
		template <typename T>
		class vector3d
		{
		public:
			vector3d() : x(0), y(0), z(0) {}
			vector3d(T nx, T ny, T nz) : x(nx), y(ny), z(nz) {}
			explicit vector3d(T n) : x(n), y(n), z(n) {}
			vector3d(const vector3d &other) : x(other.x), y(other.y), z(other.z) {}

			vector3d<T> operator-() const { return vector3d<T>(-x, -y, -z); }

			vector3d<T> operator=(const vector3d<T> &other) { x = other.x; y = other.y; z = other.z; return *this; }

			vector3d<T> operator+(const vector3d<T> &other) const { return vector3d<T>(x + other.x, y + other.y, z + other.z); }
			vector3d<T> &operator+=(const vector3d<T> &other) { x += other.x; y += other.y; z += other.z; return *this; }

			vector3d<T> operator-(const vector3d<T> &other) const { return vector3d<T>(x - other.x, y - other.y, z - other.z); }
			vector3d<T> &operator-=(const vector3d<T> &other) { x -= other.x; y -= other.y; z -= other.z; return *this; }

			vector3d<T> operator*(const T v) const { return vector3d<T>(x * v, y * v, z * v); }
			vector3d<T> &operator*=(const T v) { x *= v; y *= v; z *= v; return *this; }

			vector3d<T> operator/(const T v) const { T tmp = (T)(1.0 / v); return vector<T>(x * tmp, y * tmp, z * tmp); }
			vector3d<T> &operator/=(const T v) { T tmp = (T)(1.0 / v); x *= tmp; y *= tmp; z *= tmp; return *this; }

			bool operator==(const vector3d<T> &other) const { return equals(other); }
			bool operator!=(const vector3d<T> &other) const { return !equals(other); }

			bool equals(const vector3d<T> &other) const
			{
				return core::equals(x, other.x) && core::equals(y, other.y) && core::equals(z, other.z);
			}

			vector3d<T> &set(const T nx, const T ny, const T nz) { x = nx; y = ny; z = nz; return *this; }
			vector3d<T> &set(const vector3d<T> &other) { x = other.x; y = other.y; z = other.z; return *this; }

			T getLength() const { return static_cast<T>(sqrt(x * x, y * y, z * z)); }
			T getLengthSQ() const { return x * x + y * y + z * z; }

			T dotProduct(const vector3d<T> &other) const { return x * other.x + y * other.y + z * other.z; }
			vector3d<T> crossProduct(const vector3d<T> &other) const 
			{
				return vector3d<T>(y * other.z - other.y * z, z * other.x - x * other.z, x * other.y - y * other.x); 
			}

			T getDistanceFrom(const vector3d<T> &other) const
			{
				return vector3d<T>(x - other.x, y - other.y, z - other.z).getLength();
				//return static_cast<T>(sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z)));
			}

			T getDistanceFromSQ(const vector3d<T> &other) const
			{
				return vector3d<T>(x - other.x, y - other.y, z - other.z).getLengthSQ();
				// return static_cast<T>((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));
			}

			vector3d<T> &normalize()
			{
				double length = static_cast<double>(x * x + y * y + z * z);
				if (0 == length)
					return *this;
				length = 1 / sqrt(length);
				x *= static_cast<T>(length);
				y *= static_cast<T>(length);
				z *= static_cast<T>(length);
				return *this;
			}

			vector3d &setLength(T length)
			{
				normalize();
				return (*this *= length);
			}

			vector3d &invert()
			{
				x *= -1;
				y *= -1;
				z *= -1;
				return *this;
			}

			void rotateXZBy(double radians, const vector3d<T> &center = vector3d<T>())
			{
				double cs = cos(radians);
				double sn = sin(radians);
				x -= center.x;
				z -= center.z;
				set((T)(x * cs + z * sn), y, (T)(-x * sn + z * cs));
				x += center.x;
				z += center.z;
			}

			//Left-handed coordinate system is the same as right-handed coordinate system.
			void rotateXYBy(double radians, const vector3d<T> &center = vector3d<T>())
			{
				double cs = cos(radians);
				double sn = sin(radians);

				x -= center.x;
				y -= center.y;
				set((T)(x * cs - y * sn), (T)(x * sn + y * cs), z);
				x += center.x;
				y += center.y;
			}

			//Left-handed coordinate system is the same as right-handed coordinate system.
			void rotateYZBy(double radians, const vector3d<T> &center = vector3d<T>())
			{
				double cs = cos(radians);
				double sn = sin(radians);

				y -= center.y;
				z -= center.z;
				set(x, (T)(y * cs - z * sn), (T)(y * sn + z * cs));
				y += center.y;
				z += center.z;
			}

			vector3d<T> getInterpolated(const vector3d<T> &other, double d) const
			{
				const double inv = 1.0 - d;
				return vector3d<T>((T)(x * d + other.x * inv), (T)(y * d + other.y * inv));
			}


			vector3d<T> & interpolate(const vector3d<T> &a, const vector3d<T> &b, double d)
			{			
				x = (T)((double)b.x + ((double)(a.x - b.x)) * d);
				y = (T)((double)b.y + ((double)(a.y - b.y)) * d);
				z = (T)((double)b.z + ((double)(a.z - b.z)) * d);
			}

			//Get the rotations that would make a (0,0,1) direction vector point in the same direction as this direction vector.
			//(0, 0, 1) rotates radians.x radians by x and rotate radians.y radians by y.
			vector3d<T> getHorizontalAngle() const
			{
				vector3d<T> radians;

				const double tmp = (atan2((double)x, (double)z));
				radians.y = (T)tmp;

				if (radians.y < 0)
					radians.y += static_cast<T>(PI64 * 2);
				if (radians.y >= static_cast<T>(PI64 * 2))
					radians.y -= static_cast<T>(PI64 * 2);

				const double z1 = sqrt(x*x + z*z);

				radians.x = (T)(atan2((double)z1, (double)y) - PI64 * 0.5);

				if (radians.x < 0)
					radians.x += static_cast<T>(PI64 * 2);
				if (radians.x >= static_cast<T>(PI64 * 2))
					radians.x -= static_cast<T>(PI64 * 2);

				return radians;
			}

			// Builds a direction vector from (this) rotation vector.
			vector3d<T> rotationToDirection(const vector3d<T> & forwards = vector3d<T>(0, 0, 1)) const
			{
				const double cr = cos(x);
				const double sr = sin(x);
				const double cp = cos(y);
				const double sp = sin(y);
				const double cy = cos(z);
				const double sy = sin(z);

				const double srsp = sr*sp;
				const double crsp = cr*sp;

				const double pseudoMatrix[] = {
					(cp*cy), (cp*sy), (-sp),
					(srsp*cy - cr*sy), (srsp*sy + cr*cy), (sr*cp),
					(crsp*cy + sr*sy), (crsp*sy - sr*cy), (cr*cp) };

				return vector3d<T>(
					(T)(forwards.x * pseudoMatrix[0] +
					forwards.y * pseudoMatrix[3] +
					forwards.z * pseudoMatrix[6]),
					(T)(forwards.x * pseudoMatrix[1] +
					forwards.y * pseudoMatrix[4] +
					forwards.z * pseudoMatrix[7]),
					(T)(forwards.x * pseudoMatrix[2] +
					forwards.y * pseudoMatrix[5] +
					forwards.z * pseudoMatrix[8]));
			}

			T x;
			T y;
			T z;
		};

		template <>
		inline vector3d<int> vector3d<int>::operator/(int val) const { return core::vector3d<int>(x / val, y / val, z / val); }
		inline vector3d<int> &vector3d<int>::operator/=(int val) { x /= val; y /= val; z /= val; return *this; }		

		template <typename S, typename T>
		vector3d<T> operator*(const S scalar, const vector3d<T> &vector) { return vector * scalar; }


		typedef vector3d<float> vector3df;
	}
}

#endif