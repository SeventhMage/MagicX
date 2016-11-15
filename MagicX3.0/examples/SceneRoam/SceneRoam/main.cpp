#include "mx.h"
#include <Windows.h>
#include "..\..\..\source\render\opengl\GL\glew.h"
#include <vector>
#include <time.h>

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

	std::vector<CSphere *> vecSphere;

	CSphere *pSphere = nullptr; 
	ICamera *camera = nullptr;
	if (scene)
	{
		pSphere = new CSphere(scene);
		

		CVector3 vDir(0, 0, -1);
		CVector3 vUp(0, 1, 0);
		//camera = scene->SetupCamera(CVector3(0, 0, 5), vDir, vUp, PI / 2, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		camera = scene->SetupCamera(20.f, pSphere, vDir, vUp, PI / 2, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		scene->SetupSkyBox("texture/FullMoonLeft2048.tga", "texture/FullMoonRight2048.tga", "texture/FullMoonUp2048.tga", "texture/FullMoonDown2048.tga", "texture/FullMoonFront2048.tga", "texture/FullMoonBack2048.tga", 512);
		//scene->SetupSkyBox("texture/CloudyLightRaysLeft2048.tga", "texture/CloudyLightRaysRight2048.tga", "texture/CloudyLightRaysUp2048.tga", "texture/CloudyLightRaysDown2048.tga", "texture/CloudyLightRaysFront2048.tga", "texture/CloudyLightRaysBack2048.tga", 512);
		//scene->SetupSkyBox("texture/DarkStormyLeft2048.tga", "texture/DarkStormyRight2048.tga", "texture/DarkStormyUp2048.tga", "texture/DarkStormyDown2048.tga", "texture/DarkStormyFront2048.tga", "texture/DarkStormyBack2048.tga", 512);
		//scene->SetupSkyBox("texture/SunSetLeft2048.tga", "texture/SunSetRight2048.tga", "texture/SunSetUp2048.tga", "texture/SunSetDown2048.tga", "texture/SunSetFront2048.tga", "texture/SunSetBack2048.tga", 512);
		//scene->SetupSkyBox("texture/ThickCloudsWaterLeft2048.tga", "texture/ThickCloudsWaterRight2048.tga", "texture/ThickCloudsWaterUp2048.tga", "texture/ThickCloudsWaterDown2048.tga", "texture/ThickCloudsWaterFront2048.tga", "texture/ThickCloudsWaterBack2048.tga", 512);
		//scene->SetupSkyBox("texture/TropicalSunnyDayLeft2048.tga", "texture/TropicalSunnyDayRight2048.tga", "texture/TropicalSunnyDayUp2048.tga", "texture/TropicalSunnyDayDown2048.tga", "texture/TropicalSunnyDayFront2048.tga", "texture/TropicalSunnyDayBack2048.tga", 512);

		
		pSphere->Create(5, 52, 26);
		pSphere->SetPosition(CVector3(0, 0, 0));
		scene->GetRootNode()->AddChild(pSphere);

		srand(time(0));
		int count = 100;
		for (int i = 0; i < count; ++i)
		{
			vecSphere.push_back(new CSphere(scene));
			int r = rand() % 10;
			if (r == 0)
				r = 1;
			vecSphere[i]->Create(r, r * 10, r * 5);
			vecSphere[i]->SetPosition(CVector3(rand() % 512 - 256, rand() % 512 - 256, rand() % 512 - 256));
			scene->GetRootNode()->AddChild(vecSphere[i]);
		}

	}

	uint next_game_tick = GetTickCount();
	int sleep_time = 0;

	bool bQuit = false;
	while (device->Run())
	{
		uint cur_time = GetTickCount();
		sleep_time = next_game_tick - cur_time;
		if (sleep_time <= 0)
		{
			if (event)
			{
				static int lastX;
				static int lastY;

				int currentX = event->GetMousePositonX();
				int currentY = event->GetMousePositionY();

				float rotY = (currentX - lastX) * 2.0f * PI / device->GetWindowWidth();
				float rotX = (currentY - lastY) * 2.0f * PI / device->GetWindowHeight();

				CVector3 camDir = camera->GetDirection();
				CVector3 curRot = pSphere->GetRotation();
				if (event->IsPress(EKP_MOUSE_LBUTTON))
				{				
					if (!ISZERO(rotX) || !ISZERO(rotY))
					{
						CVector3 rot(rotX + curRot.x, curRot.y + rotY, 0);
						pSphere->SetRotation(rot);
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
					}

				}

				
				
				if (event->IsPress(EKP_KEYBOARD_A))
				{
					CVector3 leftDir = camDir;
					leftDir.rotateXZBy(PI / 2);
					pSphere->SetPosition(pSphere->GetPosition() + leftDir * 1.0f);
				}

				if (event->IsPress(EKP_KEYBOARD_D))
				{
					CVector3 rightDir = camDir;
					rightDir.rotateXZBy(PI / 2);
					pSphere->SetPosition(pSphere->GetPosition() - rightDir * 1.0f);
				}

				if (event->IsPress(EKP_KEYBOARD_W))
				{
					//camera->SetPosition(camera->GetPosition() + camDir * 1.0f);
					pSphere->SetPosition(pSphere->GetPosition() + camDir * 1.0f);
				}

				if (event->IsPress(EKP_KEYBOARD_S))
				{
					//camera->SetPosition(camera->GetPosition() - camDir * 1.0);
					pSphere->SetPosition(pSphere->GetPosition() - camDir * 1.0f);
				}

				if (event->IsPress(EKP_KEYBOARD_N))
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}

				if (event->IsPress(EKP_KEYBOARD_ESC))
				{
					exit(1);
				}

				lastX = event->GetMousePositonX();
				lastY = event->GetMousePositionY();
			}

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

	delete pSphere;
	DestroyMagicX();
	return 0;
}