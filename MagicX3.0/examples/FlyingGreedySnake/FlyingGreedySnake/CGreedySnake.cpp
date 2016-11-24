#include "CGreedySnake.h"


static const int FRAMES_PER_SECOND = 30;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

CGreedySnake::~CGreedySnake()
{
	DestroyMagicX();
}


void CGreedySnake::InitGame(int width, int height, bool fullscreen)
{
	CreateMagicX(RDT_OPENGL, 0, 0, 800, 600);
	
	IScene *scene = SCENEMGR->GetCurrentScene();
	if (scene)
	{
		//scene->SetupCamera(100.f, pSphere, vDir, vUp, PI / 3, 1.0f * device->GetWindowWidth() / device->GetWindowHeight(), 1.0f, 5000.0f);
	}
}


void CGreedySnake::Run()
{
	uint next_game_tick = GetTickCount();
	int sleep_time = 0;

	IDevice *device = DEVICEMGR->GetDevice();
	bool bQuit = false;
	while (device->Run())
	{
		uint cur_time = GetTickCount();
		sleep_time = next_game_tick - cur_time;
		if (sleep_time <= 0)
		{
			next_game_tick = GetTickCount() + SKIP_TICKS;
			bQuit = Update(SKIP_TICKS - sleep_time);
			device->SwapBuffers();
		}
		else
		{
			device->Sleep(sleep_time);
		}
	}
}


bool CGreedySnake::Update(int delta)
{
	IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
	IDevice *device = DEVICEMGR->GetDevice();
	ICamera *camera = nullptr;

	IScene *scene = SCENEMGR->GetCurrentScene();
	if (scene)
	{
		camera = scene->GetCamera();
	}
	
	if (event)
	{
		static int lastX;
		static int lastY;

		int currentX = event->GetMousePositonX();
		int currentY = event->GetMousePositionY();

		float rotY = (currentX - lastX) * 2.0f * PI / device->GetWindowWidth();
		float rotX = (currentY - lastY) * 2.0f * PI / device->GetWindowHeight();

		CVector3 camDir;

		if (event->IsPress(EKP_MOUSE_LBUTTON))
		{
			if (!ISZERO(rotX) || !ISZERO(rotY))
			{
				
				
			}
		}

		if (camera)
		{
			camDir = camera->GetDirection();
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

			int delta = event->GetWheelDelta();
			if (delta)
			{
				float dis = MIN(MAX(camera->GetDistance() - delta / 10, 10), 200);
				camera->SetDistance(dis);
			}
		}

		if (event->IsPress(EKP_KEYBOARD_A))
		{
			CVector3 leftDir = camDir;
			leftDir.rotateXZBy(PI / 2);
			//pSphere->SetPosition(pSphere->GetPosition() + leftDir * 1.0f);
		}

		if (event->IsPress(EKP_KEYBOARD_D))
		{
			CVector3 rightDir = camDir;
			rightDir.rotateXZBy(PI / 2);
			//pSphere->SetPosition(pSphere->GetPosition() - rightDir * 1.0f);
		}

		if (event->IsPress(EKP_KEYBOARD_W))
		{
			//pSphere->SetPosition(pSphere->GetPosition() + camDir * 1.0f);
		}

		if (event->IsPress(EKP_KEYBOARD_S))
		{
			//pSphere->SetPosition(pSphere->GetPosition() - camDir * 1.0f);
		}

		if (event->IsPress(EKP_KEYBOARD_ESC))
		{
			return false;
		}

		lastX = event->GetMousePositonX();
		lastY = event->GetMousePositionY();
	}


	SCENEMGR->Update(delta);
	SCENEMGR->Draw();

	return true;
}

