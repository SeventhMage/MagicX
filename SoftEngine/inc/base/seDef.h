#ifndef _MX_MXDEF_H_
#define _MX_MXDEF_H_

namespace se
{
#define MAX_FILE_NAME 256

#define SAFE_DEL(p) { if (p) { delete (p); (p) = nullptr; }}
#define SAFE_DEL_ARRAY(p) { if (p) { delete[] (p); (p) = nullptr; }}

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
#define FLOAT_EQUAL(a, b) (((a) - (b) > -ROUNDING_ERROR_FLOAT) && ((a) - (b) < ROUNDING_ERROR_FLOAT))
#define ISZERO(a) ((a) > -ROUNDING_ERROR_FLOAT && (a) < ROUNDING_ERROR_FLOAT)

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define NORMALIZE_TO_32BIT_COLOR(a, r, g, b) ((uint(a * 0xFF)) << 24) | ((uint(r * 0xFF)) << 16) | ((uint(g * 0xFF)) << 8) | (uint(b * 0xFF))

}

#endif