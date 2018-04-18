#include "mx.h"

using namespace mx;

int main(int argc, char *argv[])
{
	IRenderer *renderer = mx->GetRenderer();
	IDevice *device = mx->GetDevice();
	
	float *point[] = {
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		0.f, 1.f, 0.f,
		1.f, 1.f, 0.f, 0.f,
		1.f, 0.f, 1.f, 0.f,
		1.f, 0.f, 0.f, 1.f,
	};
	
	
	while (device->Run())
	{
		renderer->Clear();
		renderer->BufferData(point);
		renderer->AttributePointer(VA_POSITION, 0, sizeof(point));
		renderer->AttributePointer(VA_COLOR, 9 * sizeof(float), sizeof(point));
		renderer->DrawArray(PT_TRIANGLELIST);	
	}
	
	return 0;
}