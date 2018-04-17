#ifndef _MX_BASE_MATRIX_H_
#define _MX_BASE_MATRIX_H_

#include "vector.h"

//row-major
typedef float matrix33[9];
typedef float matrix44[16];

#define TransformVec3(out, m, in) {\
	out[0] = m[0] * in[0] + m[3] * in[1] + m[6] * in[2];\
	out[1] = m[1] * in[0] + m[4] * in[1] + m[7] * in[2];\
	out[2] = m[2] * in[0] + m[5] * in[1] + m[8] * in[2];\
}

#define TransformVec4(out, m, in) {\
	out[0] = m[0] * in[0] + m[4] * in[1] + m[8] * in[2] + m[12] * in[3];\
	out[1] = m[1] * in[0] + m[5] * in[1] + m[9] * in[2] + m[13] * in[3];\
	out[2] = m[2] * in[0] + m[6] * in[1] + m[10] * in[2] + m[14] * in[3];\
	out[3] = m[3] * in[0] + m[7] * in[1] + m[11] * in[2] + m[15] * in[3];\
}

#endif