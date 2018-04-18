#ifndef _BASE_VECTOR_H_
#define _BASE_VECTOR_H_

#include "math.h"

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];

typedef float point2[2];
typedef float point3[3];

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

#define RotateVec2(v, rad) {\
	float c = cosf(rad);\
	float s = sinf(rad);\
	float v0 = (v)[0] * c - (v)[1] * s;\
	float v1 = (v)[0] * s + (v)[1] * c;\
	(v)[0] = v0;\
	(v)[1] = v1;\
}

#define RotateXVec3(v, rad) {\
	float c = cosf(rad);\
	float s = sinf(rad);\
	float v1 = (v)[1] * c - (v)[2] * s;\
	float v2 = (v)[1] * s + (v)[2] * c;\
	(v)[1] = v1;\
	(v)[2] = v2;\
}

#define RotateYVec3(v, rad) {\
	float c = cosf(rad);\
	float s = sinf(rad);\
	float v0 = (v)[0] * c + (v)[2] * s;\
	float v2 = -(v)[0] * s + (v)[2] * c;\
	(v)[0] = v0;\
	(v)[2] = v2;\
}

#define RotateZVec3(v, rad) {\
	float c = cosf(rad);\
	float s = sinf(rad);\
	float v0 = (v)[0] * c - (v)[1] * s;\
	float v1 = (v)[0] * s + (v)[1] * c;\
	(v)[0] = v0;\
	(v)[1] = v1;\
}

#define MovePoint2(s, d){\
	s[0] += d[0];\
	s[1] += d[1];\
}

#define MovePoint3(s, d){\
	s[0] += d[0];\
	s[1] += d[1];\
	s[2] += d[2];\
}

#endif