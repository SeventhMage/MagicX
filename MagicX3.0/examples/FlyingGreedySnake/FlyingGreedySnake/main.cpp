#include "CGreedySnake.h"

using namespace mx;

static const int FRAMES_PER_SECOND = 30;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
//int WINAPI WinMain(HINSTANCE h, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	CGreedySnake::NewInstance();

	IMagicX *mx = CreateMagicX(RDT_OPENGL, 0, 0, 800, 600);
	IDevice *device = mx->GetDevice();

	uint next_game_tick = GetTickCount();
	int sleep_time = 0;

	bool bQuit = false;
	while (device->Run())
	{
		uint cur_time = GetTickCount();
		sleep_time = next_game_tick - cur_time;
		if (sleep_time <= 0)
		{
			next_game_tick = GetTickCount() + SKIP_TICKS;
			CGreedySnake::Instance()->Update(SKIP_TICKS - sleep_time);			
			device->SwapBuffers();
		}
		else
		{
			device->Sleep(sleep_time);
		}
	}

	DestroyMagicX();	
	CGreedySnake::DeleteInstance();
	return 0;
}