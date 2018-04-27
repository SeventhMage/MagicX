#include "../../include/base/vector.h"
#include "../../include/base/matrix.h"

#include <stdio.h>

int main(int argc, char *argv[]){
	vec2 v2 = {2.f, 4.f};
	NormalizeVec2(v2);
	printf("%f %f\n", v2[0], v2[1]);
	
	vec4 v4 = {3.f, 4.f, 5.f, 1.f};
	
	matrix44 m44 = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		30.f, 40.f, 50.f, 1.f
	};
	
	vec4 ov4;
	TransformVec4(ov4, m44, v4);
	printf("%f %f %f %f\n", ov4[0], ov4[1], ov4[2], ov4[3]);
	
	vec3 v_rot = {0, 0, 1};
	RotateYVec3(v_rot, PI_DIV_4);
	
	printf("%f %f %f\n", v_rot[0], v_rot[1], v_rot[2], v_rot[3]);
	vec3 move = {1, 1, 1};
	MovePoint3(v_rot, move);
	printf("%f %f %f\n", v_rot[0], v_rot[1], v_rot[2], v_rot[3]);
	matrix44 om44;
	MatrixMultiply44(om44, m44, m44);
	return 0;
}