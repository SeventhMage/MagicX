#include "se.h"
#include "..\src\render\software\CRasterizer.h"

static const int FRAMES_PER_SECOND = 60;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	CSoftEngine *se = CSoftEngine::NewInstance();

	se->InitEngine(render::RDT_SOFTWARE, 100, 100, 800, 600);
	IDevice *device = se->GetDevice();
	IResourceManager *resMgr = se->GetResourceManager();
	ISceneManager *sceneMgr = se->GetSceneManager();

	//test
	CRasterizer pRasterizer;
	uint *pDrawBuffer = new uint[device->GetWindowWidth() * device->GetWindowHeight()];
	pRasterizer.SetDrawBuffer(pDrawBuffer, device->GetWindowWidth(), device->GetWindowHeight());
	pRasterizer.DrawLine(100, 100, 200, 400, SColor(1, 1, 0, 0));
	pRasterizer.DrawCircle(100, 100, 50, SColor(1, 1, 0, 0));
	pRasterizer.DrawEllipse(200, 200, 30, 20);
	device->DrawBuffer((ubyte *)pDrawBuffer);

	//init scene
	IScene *scene = sceneMgr->LoadScene("scene/scene.scene");

	UINT next_game_tick = GetTickCount();
	int sleep_time = 0;

	bool bQuit = false;
	while (device->Run())
	{
		UINT cur_time = GetTickCount();
		sleep_time = next_game_tick - cur_time;
		if (sleep_time <= 0)
		{
			next_game_tick = GetTickCount() + SKIP_TICKS;
			
			//sceneMgr->Update(SKIP_TICKS - sleep_time);
		}
		else
		{
			device->Sleep(sleep_time);
		}
	}

	CSoftEngine::DeleteInstance();
	return 0;
}