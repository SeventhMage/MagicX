#include <iostream>
#include "../../../include/vector2d.h"
#include "../../../include/vector3d.h"
#include "../../../include/matrix44.h"
#include "../../../include/mxMath.h"
#include <windows.h>

using namespace std;
using namespace mx::core;


int main(int argc, char *argv[])
{
// 	mx::core::vector3d<float> vec(1, 2, 3);
// 	vec.normalize();
// 	cout << vec.x << ", " << vec.y << ", " << vec.z << endl;
// 	mx::core::vector3d<float> result = vec.getHorizontalAngle();
// 	cout << result.x * RADTODEG << "," << result.y * RADTODEG << "," << result.z * RADTODEG << endl;
// 	vector3d<float> result2 = result.rotationToDirection();
// 	cout << result2.x << ", " << result2.y << ", " << result2.z << endl;
// 	vec *= 3;
// 	long first = GetTickCount();
// 	cout << first << endl;
// 	for (int i = 0; i < 10000000; ++i)
// 	{
// 		equals(1, 1);
// 		equals(1l, 1l);
// 		equals(1.0f, 1.0f);
// 		equals(1.0, 1.0);
// 	}
// 
// 	cout << GetTickCount() - first << endl;
// 
// 	vector2d<int> vec2;
// 	vec2.normalize();

	CMatrix44<float>m44;
	m44[3];// = 9;
	m44(1, 2);// = 3;

	long first = GetTickCount();
	vector3d<float> vecRotate(0, 0, 1);
	m44.setRotationDegrees(10, 20, 30);
	for (int i = 0; i < 10000000; ++i)
	{
		m44.translate(vector3df(3, 4, 5));
		m44.rotate(vecRotate);
	}
	cout << GetTickCount() - first << endl;

	vector3df vec(0, 0, 1);
	m44.setRotationDegrees(0, 90.0, 0);

	m44.rotate(vec);

	vec = vector3df(0, 0, 1);
	m44.inverseRotate(vec);

	vec = vector3df(0, 0, 1);
	vec.rotateXZBy(PI * 0.5);

	m44.buildCameraLookAtMatrix(vector3df(), vector3df(), vector3df());
	m44.buildProjectiongMatrixPerspectiveFov(PI * 0.4f, 4 / 3, -1.0f, 500.0f);
	m44.buildProjectionMatrixOrtho(800, 600, -1.0f, 500.0f);

	cout << "end." << endl; 
	getchar();
	return 0;
}
