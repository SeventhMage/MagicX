#include "mx.h"

using namespace mx;


const int FRAMES_PER_SECOND = 50;      ///< FPS:50
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	IDevice *device = CreateDevice(100, 100, 800, 600, false);

	IRenderer *renderer = device->GetRenderer();
	IMesh *mesh = CResourceManager::Instance()->LoadResource("../../resource/plg/cube1.plg");

	uint next_game_tick = device->GetSystemRunTime();
	int sleep_time = 0;
	while (device->Run())
	{
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - GetTickCount();
		if (sleep_time >= 0)
		{
			if (renderer)
			{
				renderer->DrawLine(CVector3(0, 0, 0), CVector3(100, 100, 100));
				
				if (mesh)
				{
					renderer->DrawMesh(mesh);
				}
			}
			device->Sleep(sleep_time);
		}

		device->SwapBuffers();
	}

	DestroyDevice(device);
	return 0;
}