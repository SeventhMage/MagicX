#ifndef _MX_BASE_VECTOR_H_
#define _MX_BASE_VECTOR_H_

#include "math.h"

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

#define DotVec2(a, b) ((a)[0] * (b)[0] + (a)[1] * (b)[1])
#define DotVec3(a, b) ((a)[0] * (b)[0] + (a)[1] * (b)[1] + (a)[2] * (b)[2])

#define CrossVec3(c, a, b) ((c)[0] = (a)[1] * (b)[2] - (a)[2] * (b)[1]; (c)[1] = (a)[2] * (b)[0] - (a)[0] * (b)[2]; (c)[2] = (a)[0] * (b)[1] - (a)[1] * (b)[0])

#define NormalizeVec2(v) {\
	float iLength = Q_rsqrt(DotVec2(v, v));\
	v[0] *= iLength;\
	v[1] *= iLength;\
}

#define NormalizeVec3(v) {\
	float iLength = Q_rsqrt(DotVec3(v, v));\
	v[0] *= iLength;\
	v[1] *= iLength;\
	v[2] *= iLength;\
}

#define NormalizeVec4(v) {\
	NormalizeVec3(v)\
}

#define RotateX() {\
}

#define RotateY() {\
}

#define RotateZ() {\
}

#endif