#include "Cube.h"

using namespace mx;

static const int FRAMES_PER_SECOND = 60;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	IMagicX *mx = CreateMagicX(RDT_OPENGL, 0, 0, 800, 600);
	ISceneManager *sceneManager = mx->GetSceneManager();
	IScene *scene = sceneManager->GetCurrentScene();
	IDevice *device = mx->GetDevice();
	IEntityManager *entityMgr = mx->GetEntityManager();

	CubeVertex cubeVertice;

	if (scene)
	{
		ISceneNode *rootNode = scene->GetRootNode();
		if (rootNode)
		{
			
			IEntity *cubeEntity = entityMgr->CreateEntity(&cubeVertice, "texture/crate.tga");
			rootNode->AddChild(cubeEntity);
			//CUnit *pUnit = new CUnit;
			//pUnit->LoadModel("");
			//rootNode->AddChild(pUnit);

		}
	}

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

			sceneManager->Update(SKIP_TICKS - sleep_time);
			sceneManager->Draw();
			device->SwapBuffers();
		}
		else
		{
			device->Sleep(sleep_time);
		}
	}

	return 0;
}