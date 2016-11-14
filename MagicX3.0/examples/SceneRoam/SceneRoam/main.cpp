#include "mx.h"
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

	CSphere *pSphere = nullptr; 
	ICamera *camera = nullptr;
	if (scene)
	{
		pSphere = new CSphere(scene);
		CVector3 vDir(0, 0, -1);
		CVector3 vUp(0, 1, 0);
		camera = scene->SetupCamera(CVector3(0, 0, 5), vDir, vUp, PI / 2, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		//camera = scene->SetupCamera(10.f, pSphere, vDir, vUp, PI / 2, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		scene->SetupSkyBox("texture/pos_z.tga", "texture/neg_z.tga", "texture/neg_x.tga", "texture/pos_x.tga", "texture/pos_y.tga", "texture/neg_y.tga", 100);
		
		//pSphere = new CSphere(scene, 5, 10, 10);
		pSphere->Create(5, 20, 20);
		pSphere->SetPosition(CVector3(0, 0, -10));
		scene->GetRootNode()->AddChild(pSphere);
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

				if (event->IsPress(EKP_MOUSE_LBUTTON))
				{
					CVector3 curRot = pSphere->GetRotation();
					CVector3 rot(rotX + curRot.x, curRot.y + rotY, 0);
					pSphere->SetRotation(rot);
				}
				if (event->IsPress(EKP_MOUSE_RBUTTON))
				{

				}

				CVector3 camDir = camera->GetDirection();
				
				if (event->IsPress(EKP_KEYBOARD_A))
				{
					
				}

				if (event->IsPress(EKP_KEYBOARD_D))
				{
					
				}

				if (event->IsPress(EKP_KEYBOARD_W))
				{
					camera->SetPosition(camera->GetPosition() + camDir * 1.0);
				}

				if (event->IsPress(EKP_KEYBOARD_S))
				{
					camera->SetPosition(camera->GetPosition() - camDir * 1.0);
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