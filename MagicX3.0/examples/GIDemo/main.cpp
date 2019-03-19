#include "mx.h"
#include "CSphereEntity.h"
#include "CHouse.h"

#include <time.h>
#include <Windows.h>


using namespace mx;

static const int FRAMES_PER_SECOND = 60;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	IMagicX *mx = CreateMagicX(RDT_OPENGL, 0, 0, 800, 600);
	ISceneManager *sceneManager = mx->GetSceneManager();
	IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
	IScene *scene = sceneManager->GetCurrentScene();
	IDevice *device = mx->GetDevice();

	float yellow[] = { 8.f, .8f, .1f, 1.f };
	float gray[] = { .8f, .8f, .8f, 1.f };


	ex::CHouse *pHouse = new ex::CHouse(100, 100, 100);
	CPointLight *pPointLight = nullptr;
	ICamera *camera = nullptr;
	CScreenAlignedQuad *pScreenAlignedQuad = new CScreenAlignedQuad(3, 5);
	if (scene)
	{
		CVector3 vPos(0, 0, 10);
		CVector3 vDir(0, 0, -1);
		CVector3 vUp(0, 1, 0);
		camera = scene->SetupCamera(vPos, vDir, vUp, PI / 3, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		//scene->SetupSkyBox("texture/TropicalSunnyDayLeft2048.tga", "texture/TropicalSunnyDayRight2048.tga", "texture/TropicalSunnyDayUp2048.tga", "texture/TropicalSunnyDayDown2048.tga", "texture/TropicalSunnyDayFront2048.tga", "texture/TropicalSunnyDayBack2048.tga", 256);		



		srand(time(0));
		for (int i = 0; i < 64; ++i)
		{
			CVector3 lightPos(rand() % 100 - 50, rand() % 100 - 50, rand() % 100 - 50);
			CVector3 lightColor(1.f * (rand() % 256) / 25600, 1.f * (rand() % 256) / 25600, 1.f * (rand() % 256) / 25600);
			lightPos.set(0, 0, 0);
			lightColor.set(1, 1, 1);
			CPointLight *pLight = (CPointLight *)scene->SetupLight(i, LT_POINT, lightColor.v);
			pLight->SetPosition(lightPos);
			scene->SetupLightCamera(i, lightPos, -lightPos, CVector3(0, 1, 0), PI * 0.5f, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1, 1000.f);
		}


		pHouse->SetPosition(CVector3(0, 0, -150));
		scene->GetRootNode()->AddChild(pHouse);

	}
	srand(time(0));
	for (int i = 0; i < 10; ++i)
	{
		ex::CSphereEntity *pSphere = new ex::CSphereEntity(5, 52, 26);
		float x = rand() % 100 - 50;
		float y = rand() % 100 - 50;
		float z = -130.f;
		pSphere->Create();
		pSphere->SetPosition(CVector3(x, y, z));
		scene->GetRootNode()->AddChild(pSphere);
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
			pScreenAlignedQuad->Render();
			mx->Run(SKIP_TICKS - sleep_time);

			if (event)
			{
				static int lastX;
				static int lastY;

				int currentX = event->GetMousePositonX();
				int currentY = event->GetMousePositionY();

				float rotY = (currentX - lastX) * 2.0f * PI / device->GetWindowWidth();
				float rotX = (currentY - lastY) * 2.0f * PI / device->GetWindowHeight();

				CVector3 camDir = camera->GetDirection();

				if (event->IsPress(EKP_MOUSE_LBUTTON))
				{

				}
				if (event->IsPress(EKP_MOUSE_RBUTTON))
				{
					if (!ISZERO(rotX) || !ISZERO(rotY))
					{
						camDir.rotateXZBy(-rotY);
						CMatrix4 rotMat4;
						rotMat4.SetRotationRadians(rotX, (-camDir).crossProduct(CVector3(0, 1.0f, 0)));
						rotMat4.TransformVect(camDir);

						camDir.normalize();
						camera->SetDirection(camDir);
					}

				}

				if (event->IsPress(EKP_KEYBOARD_ESC))
				{
					exit(1);
				}

				lastX = event->GetMousePositonX();
				lastY = event->GetMousePositionY();
			}

		}
		else
		{
			device->Sleep(sleep_time);
		}


	}
	DestroyMagicX();
	return 0;
}