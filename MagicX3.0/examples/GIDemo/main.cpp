#include "mx.h"
#include "CSphereEntity.h"
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

	ex::CSphereEntity *pSphere = nullptr;
	ex::CSphereEntity *pSphereSun = nullptr;
	CPointLight *pPointLight = nullptr;
	ICamera *camera = nullptr;
	CScreenAlignedQuad *pScreenAlignedQuad = new CScreenAlignedQuad(2, 5);
	if (scene)
	{

		pSphere = new ex::CSphereEntity(5, 52, 26);
		pSphereSun = new ex::CSphereEntity(2, 26, 13);

		CVector3 vDir(0, -1, -1);
		CVector3 vUp(0, 1, 0);
		//camera = scene->SetupCamera(CVector3(0, 0, 5), vDir, vUp, PI / 3, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		camera = scene->SetupCamera(100.f, pSphere, vDir, vUp, PI / 3, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		//scene->SetupSkyBox("texture/TropicalSunnyDayLeft2048.tga", "texture/TropicalSunnyDayRight2048.tga", "texture/TropicalSunnyDayUp2048.tga", "texture/TropicalSunnyDayDown2048.tga", "texture/TropicalSunnyDayFront2048.tga", "texture/TropicalSunnyDayBack2048.tga", 256);		
		pPointLight = (CPointLight *)scene->SetupLight(0, LT_POINT, yellow);

		pSphere->Create();
		pSphere->SetPosition(CVector3(0, 30, 0));
		scene->GetRootNode()->AddChild(pSphere);

		pSphereSun->Create();
		pSphereSun->SetPosition(CVector3(10, 50, -10));
		scene->GetRootNode()->AddChild(pSphereSun);

		pPointLight->SetPosition(pSphereSun->GetPosition());
		scene->SetupLightCamera(0, pPointLight->GetPosition(), -pPointLight->GetPosition(), CVector3(0, 1, 0), PI * 0.5f, 1.f, 1.f, 1000.f);
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