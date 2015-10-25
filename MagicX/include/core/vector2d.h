#ifndef _MX_VECTOR_2D_H_INC_
#define _MX_VECTOR_2D_H_INC_

#include "common/mxMath.h"

namespace mx
{
	namespace core
	{
		template <typename T>
		class vector2d
		{
		public:
			vector2d() : x(0), y(0){}
			vector2d(T nx, T ny) : x(nx), y(ny){}
			explicit vector2d(T n) : x(n), y(n){}
			vector2d(const vector2d<T> &other) : x(other.x), y(other.y){}
		
			//operators
			vector2d<T> operator-() const { return vector2d<T>(-x, -y); }

			vector2d<T> &operator=(const vector2d<T> &other) { x = other.x; y = other.y; return *this; }

			vector2d<T> operator+(const vector2d<T> &other) const { return vector2d<T>(x + other.x, y + other.y); }
			vector2d<T> &operator+=(const vector2d<T> &other) { x += other.x; y += other.y; return *this; }
		
			vector2d<T> operator-(const vector2d<T> &other) const { return vector2d<T>(x - other.x, y - other.y); }
			vector2d<T> &operator-=(const vector2d<T> &other) { x -= other.x; y -= other.y; return *this; }

			vector2d<T> operator*(const T v) const { return vector2d<T>(x * v, y * v); }
			vector2d<T> &operator*=(const T v) { x *= v; y *= v; return *this; }

			vector2d<T> operator/(const T v) const { return vector2d<T>(x / v, y / v); }
			vector2d<T> &operator/=(const T v) { x /= v; y /= v; return *this; }

			bool operator==(const vector2d<T> &other) const { return equals(other); }
			bool operator!=(const vector2d<T> &other) const { return !equals(other); }


			//functions
			bool equals(const vector2d<T> & other)const
			{
				return core::equals(x, other.x) && core::equals(y, other.y);
			}

			vector2d &set(T nx, T ny) { x = nx; y = ny; return *this; }
			vector2d &set(const vector2d<T> &other) { x = other.x; y = other.y; return *this; }

			T getLength() const { return static_cast<T>(sqrt(static_cast<double>((x * x + y * y)))); }
			T getLengthSQ() const { return x * x + y * y; }
		
			T doProduct(const vector2d<T> &other) const { return x * other.x + y * other.y; }

			T getDistanceFrom(const vector2d &other) const
			{
				return static_cast<T>(sqrt(static_cast<double>((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y))));
				//return vector2d<T>(x - other.x, y - other.y).getLength(); //和上面相比哪个效率更高？
			}
			T getDistanceFromSQ(const vector2d &other) const
			{
				return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
				//return vector2d<T>(x - other.x, y - other.y).getLength(); //和上面相比哪个效率更高？
			}

			vector2d &rotateBy(double radian, const vector2d<T> &center = vector2d<T>())
			{
				const double cs = cos(radian);
				const double sn = sin(radian);

				x -= center.x;
				y -= center.y;

				set((T)(x * cs - y * sn), (T)(x * sn + y * cs));

				x += center.x;
				y += center.y;
				return *this;
			}

			vector2d &normalize()
			{
				float length = (float)(x * x + y * y);
				if (0 == length)
					return *this;
				length = 1 / sqrt(length);
				x *= (T)length;
				y *= (T)length;
				return *this;
			}

			/*
			* x-axis is right and y-axis is up, values increase counter-clockwise
			* x-axis is right and y-axis is down, values increase clockwise
			* return a value between 0 and 2PI
			*/
			inline double getRadian() const
			{
				if (y == 0)
					return x < 0 ? PI64 : 0;
				else
				{
					if (x == 0)
						return y < 0 ? PI64 * 1.5 : PI64 * 0.5;
				}

				const double raidan = atan(y / x);

				if (x > 0)
				{
					if (y > 0)
						return raidan;
					else
						return PI64 * 2 + raidan;
				}
				else
				{
					return PI64 + raidan;
				}
			}

			/*
			*return radian between this and other, the value between 0 and PI
			*/
			inline double getRadianWidth(const vector2d<T> &other) const
			{
				double tmp = x * other.x + y * other.y;
				if (iszero(tmp))
					return PI * 0.5;

				tmp /= sqrt((x * x + y * y) * (other.x * other.x + other.y * other.y));

				return acos(tmp);
			}

			vector2d<T> getInterpolated(const vector2d<T> &other, double d)const
			{
				double inv = 1.0 - d;
				return vector2d<T>((T)(other.x * inv + x * d), (T)(other.y * inv + y * d));
			}

			vector2d<T> &interpolate(const vector2d<T> &a, const vector2d &b, double d)
			{
				x = (double)((double)b.x + (a.x - b.x) * d);
				y = (double)((double)b.y + (a.y - b.y) * d);
				return *this;
			}

			T x;
			T y;
		};

		typedef vector2d<float> vector2df;
		typedef vector2d<int> vector2di;

		template<class S, class T>
		vector2d<T> operator*(const S scalar, const vector2d<T>& vector) { return vector*scalar; }
	}
}

#endif