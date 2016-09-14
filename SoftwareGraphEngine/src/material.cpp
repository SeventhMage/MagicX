#include "material.h"


MATV1 materials[MAX_MATERIALS];
int num_materials;

void Reset_Materials_MATV1()
{
	static int first_time = 1;
	if (first_time)
	{
		memset(materials, 0, MAX_MATERIALS*sizeof(MATV1));
		first_time = 0;
	}
	for (int curr_matt = 0; curr_matt < MAX_MATERIALS; ++curr_matt)
	{
		Destroy_Bitmap(&materials[curr_matt].texture);
		memset(&materials[curr_matt], 0, sizeof(MATV1));
	}
}
