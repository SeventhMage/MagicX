#ifndef _MX_MATH_H_INC_
#define _MX_MATH_H_INC_

#include <typeinfo>
#include <cstring>

namespace mx
{
	namespace core
	{
		const float ROUNDING_ERROR_FLOAT = 0.000001f;
		const double ROUNDING_ERROR_DOUBLE = 0.00000001;

		const float PI = 3.14159265359f;
		const double PI64 = 3.1415926535897932384626433832795028841971693993751;

		const float DEGTORAD = PI / 180.0f;
		const float RADTODEG = 180.0f / PI;
		const double DEGTORAD64 = PI64 / 180.0f;
		const double RADTODEG64 = 180.0f / PI64;

		#define DEG_TO_RAD(x)	((x)*DEGTORAD)
		#define RAD_TO_DEG(x)	((x)*RADTODEG)

	//RTTI Ð§ÂÊµÍÏÂ
	// 	template <typename T>
	// 	inline bool equals(T a, T b)
	// 	{
	// 		if (!std::strcmp(typeid(T).name(), typeid(0).name()))
	// 		{
	// 			return a == b;
	// 		}
	// 		else if (!std::strcmp(typeid(T).name(), typeid(0l).name()))
	// 		{
	// 			return a == b;
	// 		}
	// 		else if (!std::strcmp(typeid(T).name(), typeid(0.0f).name()))
	// 		{
	// 			return (a - ROUNDING_ERROR_FLOAT <= b) && (a + ROUNDING_ERROR_FLOAT >= b);
	// 		}
	// 		else if (!std::strcmp(typeid(T).name(), typeid(0.0).name()))
	// 		{
	// 			return (a - ROUNDING_ERROR_DOUBLE <= b) && (a + ROUNDING_ERROR_DOUBLE >= b);
	// 		}
	// 		return false;
	// 	}

		template <typename T>
		inline bool equals(T a, T b)
		{
			return a == b;
		}

		template <>
		inline bool equals(float a, float b)
		{
			return (a - ROUNDING_ERROR_FLOAT <= b) && (a + ROUNDING_ERROR_FLOAT >= b);
		}

		template<>
		inline bool equals(double a, double b)
		{
			return (a - ROUNDING_ERROR_DOUBLE <= b) && (a + ROUNDING_ERROR_DOUBLE >= b);
		}

		template <typename T>
		inline bool iszero(const T a)
		{
			return equals(a, 0);
		}

		template <typename T>
		inline const T &mx_max(const T &a, const T &b)
		{
			return a < b ? b : a;
		}

		template <typename T>
		inline const T &mx_min(const T &a, const T &b)
		{
			return a < b ? a : b;
		}

		template <typename T>
		inline const T &mx_clamp(const T &value, const T &low, const T &high)
		{
			return mx_max(mx_min(value, high), low);
		}
	}
}

#endif