#include "se.h"
#include "..\src\render\software\CRasterizer.h"
#include <ctime>

static const int FRAMES_PER_SECOND = 100;
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	std::srand(time(0));
	CSoftEngine *se = CSoftEngine::NewInstance();

	se->InitEngine(render::RDT_SOFTWARE, 100, 100, 800, 600);
	IDevice *device = se->GetDevice();
	IResourceManager *resMgr = se->GetResourceManager();
	ISceneManager *sceneMgr = se->GetSceneManager();
	IRenderer *pRender = se->GetRenderer();
	IObjectManager *objectMgr = se->GetObjectManager();
	//test
	//CRasterizer pRasterizer;
	//uint *pDrawBuffer = new uint[device->GetWindowWidth() * device->GetWindowHeight()];
	//pRasterizer.SetDrawBuffer(pDrawBuffer, device->GetWindowWidth(), device->GetWindowHeight());
	//pRasterizer.DrawLine(100, 100, 200, 400, SColor(1, 1, 0, 0));
	//pRasterizer.DrawCircle(100, 100, 50, SColor(1, 1, 0, 0));
	//pRasterizer.DrawEllipse(200, 200, 30, 20);
	//device->DrawBuffer((ubyte *)pDrawBuffer);

	//init scene
	IScene *scene = sceneMgr->LoadScene("scene/scene.scene");

	objectMgr->CreateSphere(10, Color(1, 1, 0, 0));

	unsigned long long next_game_tick = device->GetSystemRunTime();
	unsigned long long sleep_time = 0;

	char buf[256] = { 0 };
	int delta = 0;
	bool bQuit = false;
	while (device->Run())
	{
		unsigned long long cur_time = device->GetSystemRunTime();
		sleep_time = next_game_tick - cur_time;
		if (sleep_time <= 0)
		{
			next_game_tick = device->GetSystemRunTime() + SKIP_TICKS;
			
			delta = SKIP_TICKS - sleep_time;
		
			sceneMgr->Update(delta);				

			sprintf_s(buf, "delta:%d frame:%d triangle:%u", delta, 1000 / delta, pRender->GetTriangleNum());
			pRender->DrawText(0, 0, buf, strlen(buf));
		}
		else
		{
			device->Sleep(sleep_time);
		}
	}

	CSoftEngine::DeleteInstance();
	return 0;
}