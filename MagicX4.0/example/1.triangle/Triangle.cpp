#include "mx.h"

using namespace mx;

static const int FRAMES_PER_SECOND = 60;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;


int main(int argc, char *argv[])
{
	IRenderer *renderer = magic->GetRenderer();
	IDevice *device = magic->GetDevice();
	
	float point[] = {
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		0.f, 1.f, 0.f,
		1.f, 1.f, 0.f, 0.f,
		1.f, 0.f, 1.f, 0.f,
		1.f, 0.f, 0.f, 1.f,
	};
	
	unsigned long long next_game_tick = device->GetSystemRunTime();
	int sleep_time = 0;

	bool bQuit = false;
	
	while (device->Run())
	{
		unsigned long long cur_time = device->GetSystemRunTime();
		sleep_time = next_game_tick - cur_time;
		if (sleep_time <= 0)
		{
			next_game_tick = cur_time + SKIP_TICKS;

			renderer->Clear();
			renderer->BufferData(point);
			renderer->AttributePointer(VA_POSITION, 0, sizeof(point));
			renderer->AttributePointer(VA_COLOR, 9 * sizeof(float), sizeof(point));
			renderer->DrawArray(PT_TRIANGLELIST);
		}
		else
		{
			device->Sleep(sleep_time);
		}
	}
	
	return 0;
}