#include "Cube.h"

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

	ICamera *camera = nullptr;
	CubeVertex cubeVertice;
	ILight *pLight = nullptr;
	ICamera *pLightCamera = nullptr;
	CUnit *cube = new CUnit(&cubeVertice, "texture/crate.tga");
	if (scene)
	{
		CUnit *cube2 = new CUnit(&cubeVertice, "texture/neg_x.tga");
		CVector3 vDir(0, 0, -1);
		CVector3 vUp(0, 1, 0);
		float screenRate = 1.0f * device->GetWindowWidth() / device->GetWindowHeight();
		//camera = scene->SetupCamera(CVector3(0, 0, 10), vDir, vUp, PI / 6, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
		camera = scene->SetupCamera(20.f, cube, vDir, vUp, PI / 2, screenRate, 1.0f, 5000.0f);
		ISceneNode *rootNode = scene->GetRootNode();
		if (rootNode)
		{									
			rootNode->AddChild(cube);
			cube->SetPosition(CVector3(0, 0, -20));
			rootNode->AddChild(cube2);
			cube2->SetPosition(CVector3(-10, -10, -20));
		}

		CVector3 lightPos;
		CVector3 lightDir(0, 0, -1);
		CVector3 lightUp(0, 1, 0);
		CVector3 lightColor;
		lightPos.set(0, 0, 20);
		lightColor.set(1.0, 1.0, 1.0);
		pLight = (CDirectionalLight *)scene->SetupLight(0, LT_DIRECTIONAL, lightColor.v);
		((CDirectionalLight *)pLight)->SetDirection(lightDir);
		pLightCamera = scene->SetupLightCamera(0, lightPos, lightDir, lightUp, 100 * screenRate, 100, 1.f, 100.f);
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
					CVector3 curRot = cube->GetRotation();
					CVector3 rot(rotX + curRot.x, curRot.y + rotY, 0);

					static CVirtualTraceBall traceBall;
					CMatrix4 mRotate = traceBall.GetRotateMatrix(1.0f * currentX, 1.0f * currentY, 1.f * lastX, 1.f * lastY);
					mRotate.SetTranslation(cube->GetPosition());

					//mRotate = mRotate * cube->GetRelativeTransformation();
					cube->SetRelativeTransformation(mRotate);

					//cube->SetRotation(rot);
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
				CVector3 mainPos = cube->GetPosition();
				float step = .1f;
				if (event->IsPress(device::EKP_KEYBOARD_A))
				{
					mainPos.x -= step;
				}
				if (event->IsPress(device::EKP_KEYBOARD_D))
				{
					mainPos.x += step;
				}
				if (event->IsPress(device::EKP_KEYBOARD_W))
				{
					mainPos.z -= step;
				}
				if (event->IsPress(device::EKP_KEYBOARD_S))
				{
					mainPos.z += step;
				}

				if (event->IsPress(device::EKP_KEYBOARD_SPACE))
				{
					mainPos.y += step;
				}
				if (event->IsPress(device::EKP_KEYBOARD_Z))
				{
					mainPos.y -= step;
				}
				cube->SetPosition(mainPos);

				lastX = event->GetMousePositonX();
				lastY = event->GetMousePositionY();
			}

		}
		else
		{
			device->Sleep(sleep_time);
		}

		
	}
	delete cube;
	DestroyMagicX();
	return 0;
}