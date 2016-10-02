#include "light.h"

#include <string.h>

LIGHTV1 lights[MAX_LIGHTS];
int num_lights;

void Reset_Lights_LIGHTV1()
{
	static int first_time = 1;
	memset(lights, 0, MAX_LIGHTS*sizeof(LIGHTV1));
	num_lights = 0;
	first_time = 0;
}

int Init_Light_LIGHTV1(int index, int _state, int _attr, RGBAV1 _c_ambient, RGBAV1 _c_diffuse, 
	RGBAV1 _c_specular, POINT4D_PTR _pos, VECTOR4D_PTR _dir, float _kc, float _kl, float _kq, 
	float _spot_inner, float _spot_outer, float _pf)
{
	if (index < 0 || index >= MAX_LIGHTS)
		return(0);	
	lights[index].state = _state;
	lights[index].id = index;
	lights[index].attr = _attr;

	lights[index].c_ambient = _c_ambient;
	lights[index].c_diffuse = _c_diffuse;
	lights[index].c_specular = _c_specular;

	lights[index].kc = _kc;
	lights[index].kl = _kl;
	lights[index].kq = _kq;

	if (_pos)
		VECTOR4D_COPY(&lights[index].pos, _pos);

	if (_dir)
	{
		VECTOR4D_COPY(&lights[index].dir, _dir);		
		VECTOR4D_Normalize(&lights[index].dir);

	}

	lights[index].spot_inner = _spot_inner;
	lights[index].spot_outer = _spot_outer;
	lights[index].pf = _pf;
	
	return(index);
}
