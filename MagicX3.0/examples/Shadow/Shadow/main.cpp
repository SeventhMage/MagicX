#include "mx.h"
#include <Windows.h>

#include "gl/glew.h"

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

	float color[] = { 1.f, .8f, .1f, .5f };
	IRenderObject *pReflectObj = new CReflectObject();
	IRenderObject *pColorFlatObj = new CColorFlatObject(color);
	CSphereEntity *pSphere = nullptr;
	CSphereEntity *pSphereSun = nullptr;

	ICamera *camera = nullptr;
	if (scene)
	{
		
		pSphere = new CSphereEntity(pReflectObj, 5, 52, 26);
		pSphereSun = new CSphereEntity(pColorFlatObj, 2, 26, 13);

		CVector3 vDir(0, 0, -1);
		CVector3 vUp(0, 1, 0);
		//camera = scene->SetupCamera(CVector3(0, 0, 5), vDir, vUp, PI / 2, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		camera = scene->SetupCamera(20.f, pSphere, vDir, vUp, PI / 2, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);		
		scene->SetupSkyBox("texture/ThickCloudsWaterLeft2048.tga", "texture/ThickCloudsWaterRight2048.tga", "texture/ThickCloudsWaterUp2048.tga", "texture/ThickCloudsWaterDown2048.tga", "texture/ThickCloudsWaterFront2048.tga", "texture/ThickCloudsWaterBack2048.tga", 512);		

		pSphere->Create();
		pSphere->SetPosition(CVector3(0, 0, 0));
		scene->GetRootNode()->AddChild(pSphere);

		pSphereSun->Create();
		pSphereSun->SetPosition(CVector3(10, 10, -10));
		scene->GetRootNode()->AddChild(pSphereSun);
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
					pSphere->SetPosition(pSphere->GetPosition() + camDir * 1.0f);
				}

				if (event->IsPress(EKP_KEYBOARD_S))
				{
					pSphere->SetPosition(pSphere->GetPosition() - camDir * 1.0f);
				}

				if (event->IsPress(EKP_KEYBOARD_N))
				{
					glPolygonMode(GL_FRONT, GL_LINE);
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

	delete pReflectObj;
	delete pColorFlatObj;
	delete pSphere;
	delete pSphereSun;
	DestroyMagicX();
	return 0;
}