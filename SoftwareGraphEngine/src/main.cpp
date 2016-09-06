#include "sge.h"

int main(char *agrc, char *argv[])
{

	Open_Error_File("ERROR.TXT", stdout);

	// set function pointer to something
	RGB16Bit = RGB16Bit565;

	OBJECT4DV1 obj;
	VECTOR4D vScale = {1.0f, 1.0f, 1.0f, 1.0f};
	VECTOR4D vPos = { 0.0f, 0.0f, 0.0f, 0.0f };
	VECTOR4D vRot = { 0.0f, 0.0f, 0.0f, 0.0f };

	Load_OBJECT4DV1_PLG(&obj, "model/cube1.plg", &vScale, &vPos, &vRot);
	
	Close_Error_File();
	getchar();
	return 0;
}