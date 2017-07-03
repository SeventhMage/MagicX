#include "se.h"

static const int FRAMES_PER_SECOND = 60;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	CSoftEngine *se = CSoftEngine::NewInstance();

	se->InitEngine(render::RDT_SOFTWARE, 100, 100, 800, 600);
	IDevice *device = se->GetDevice();
	IResourceManager *resMgr = se->GetResourceManager();
	ISceneManager *sceneMgr = se->GetSceneManager();

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

			scene->Update(SKIP_TICKS - sleep_time);
			scene->Draw();			
		}
		else
		{
			device->Sleep(sleep_time);
		}
	}

	CSoftEngine::DeleteInstance();
	return 0;
}