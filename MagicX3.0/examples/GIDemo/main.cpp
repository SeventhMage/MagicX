#include "mx.h"
#include "CSphereEntity.h"
#include "CHouse.h"

#include <time.h>
#include <Windows.h>


using namespace mx;

static const int FRAMES_PER_SECOND = 120;      ///< FPS:50
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


	ILight *pLight[MAX_LIGHT_NUM] = { 0 };
	ICamera *pLightCamera[MAX_LIGHT_NUM] = {0};
	ex::CHouse *pHouse = new ex::CHouse(10, 10, 10);
	ICamera *camera = nullptr;
	if (scene)
	{
		CVector3 vPos(0, 0, 15);
		CVector3 vDir(0, 0, -1);
		CVector3 vUp(0, 1, 0);
		float screenRate = 1.f * device->GetWindowWidth() / device->GetWindowHeight();
		camera = scene->SetupCamera(vPos, vDir, vUp, PI / 3, screenRate, 1.0f, 1000.0f);
		//scene->SetupSkyBox("texture/TropicalSunnyDayLeft2048.tga", "texture/TropicalSunnyDayRight2048.tga", "texture/TropicalSunnyDayUp2048.tga", "texture/TropicalSunnyDayDown2048.tga", "texture/TropicalSunnyDayFront2048.tga", "texture/TropicalSunnyDayBack2048.tga", 256);		

		srand(time(0));
		CVector3 lightPos;
		CVector3 lightDir(0, -1, 0);
		CVector3 lightUp(0, 0, -1);
		CVector3 lightColor;
		lightPos.set(0, 4.9, 0);
		lightColor.set(1.0, 1.0, 1.0);
		pLight[0] = (CDirectionalLight *)scene->SetupLight(0, LT_DIRECTIONAL, lightColor.v);
		((CDirectionalLight *)pLight[0])->SetDirection(lightDir);
		pLightCamera[0] = scene->SetupLightCamera(0, lightPos, lightDir, lightUp, 20 * screenRate, 20, 1.f, 100.f);
			
		//pLight[0] = scene->SetupLight(0, LT_POINT, lightColor.v);
		//((CPointLight *)pLight[0])->SetPosition(lightPos);
		//pLightCamera[0] = scene->SetupLightCamera(0, lightPos, lightDir, lightUp, 2 * PI / 3, screenRate, 0.1f, 1000.f);

		pHouse->SetPosition(CVector3(0, 0, 0));
		scene->GetRootNode()->AddChild(pHouse);

	}
	//srand(time(0));
	//for (int i = 0; i < 1; ++i)
	//{
	//	ex::CSphereEntity *pSphere = new ex::CSphereEntity(5, 52, 26);
	//	float x = rand() % 100 - 50;
	//	float y = rand() % 100 - 50;
	//	float z = -130.f;
	//	pSphere->Create();
	//	pSphere->SetPosition(CVector3(x, y, z));
	//	scene->GetRootNode()->AddChild(pSphere);
	//}

	ex::CSphereEntity *mainSphere =  new ex::CSphereEntity(1.5, 24, 12, CVector3(1.f, 0.0f, 0.0f));
	mainSphere->Create();
	mainSphere->SetPosition(CVector3(3, -3, 0));
	scene->GetRootNode()->AddChild(mainSphere);

	ex::CSphereEntity *tmpSphere = new ex::CSphereEntity(3, 24, 12, CVector3(.5f, .8f, .5f));
	tmpSphere->Create();
	tmpSphere->SetPosition(CVector3(-1.5, -1.5, 0));
	scene->GetRootNode()->AddChild(tmpSphere);

	UINT next_game_tick = GetTickCount();
	int sleep_time = 0;
	wchar_t title[64] = { 0 };
	bool bQuit = false;
	while (device->Run())
	{
		UINT cur_time = GetTickCount();
		sleep_time = next_game_tick - cur_time;
		if (sleep_time <= 0)
		{
			next_game_tick = cur_time + SKIP_TICKS;
			int delta = 1000 / (SKIP_TICKS - sleep_time);
			_snwprintf_s(title, sizeof(title), L"FPS:%d TriangleNum:%d", delta, mx->GetRenderer()->GetTriangleNum());
			mx->Run(delta);
			device->SetWindowTitle(title);

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
					if (!ISZERO(rotX) || !ISZERO(rotY))
					{
						CVector3 pRot = pHouse->GetRotation();
						pRot.x += rotX * PI / 10;
						pRot.y += rotY * PI / 10;
						pHouse->SetRotation(pRot);
					}
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
						camera->SetPosition(-camDir * camera->GetPosition().getLength());
					}

				}

				if (mainSphere)
				{
					CVector3 spherePos = mainSphere->GetPosition();
					float step = .1f;
					if (event->IsPress(device::EKP_KEYBOARD_A))
					{
						spherePos.x -= step;
					}
					if (event->IsPress(device::EKP_KEYBOARD_D))
					{
						spherePos.x += step;
					}
					if (event->IsPress(device::EKP_KEYBOARD_W))
					{
						spherePos.z -= step;
					}
					if (event->IsPress(device::EKP_KEYBOARD_S))
					{
						spherePos.z += step;
					}

					if (event->IsPress(device::EKP_KEYBOARD_SPACE))
					{
						spherePos.y += step;
					}
					if (event->IsPress(device::EKP_KEYBOARD_Z))
					{
						spherePos.y -= step;
					}
					mainSphere->SetPosition(spherePos);
					//pLight[0]->SetPosition(spherePos);
					//pLightCamera[0]->SetPosition(spherePos);
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