#include "CGreedySnake.h"


static const int FRAMES_PER_SECOND = 30;      ///< FPS:50
static const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

CGreedySnake::CGreedySnake()
:m_pGameScene(nullptr)
{

}

CGreedySnake::~CGreedySnake()
{
	SAFE_DEL(m_pGameScene);
	DestroyMagicX();
}


void CGreedySnake::InitGame(int width, int height, bool fullscreen)
{
	CreateMagicX(RDT_OPENGL, 0, 0, 800, 600);
	m_pGameScene = new CGameScene();
	m_pGameScene->InitScene();
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
	if (!m_pGameScene)
		return true;

	CHero *pHero = m_pGameScene->GetHero();
	if (!pHero)
		return true;

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
					camDir.normalize();
					camDir.rotateXZBy(-rotY);
					//CMatrix4 rotMat4;
					//rotMat4.SetRotationRadians(rotX, (-camDir).crossProduct(CVector3(0, 1.0f, 0)));
					//rotMat4.TransformVect(camDir);

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
			pHero->SetPosition(pHero->GetPosition() + CVector3(leftDir.x, 0, leftDir.z) * 1.0f);
		}

		if (event->IsPress(EKP_KEYBOARD_D))
		{
			CVector3 rightDir = camDir;
			rightDir.rotateXZBy(PI / 2);
			pHero->SetPosition(pHero->GetPosition() - CVector3(rightDir.x, 0, rightDir.z) * 1.0f);
		}

		if (event->IsPress(EKP_KEYBOARD_W))
		{
			pHero->SetPosition(pHero->GetPosition() + CVector3(camDir.x, 0, camDir.z) * 1.0f);
		}

		if (event->IsPress(EKP_KEYBOARD_S))
		{
			pHero->SetPosition(pHero->GetPosition() - CVector3(camDir.x, 0, camDir.z) * 1.0f);
		}

		if (event->IsPress(EKP_KEYBOARD_ESC))
		{
			return false;
		}

		lastX = event->GetMousePositonX();
		lastY = event->GetMousePositionY();
	}

	m_pGameScene->Update(delta);

	SCENEMGR->Update(delta);
	SCENEMGR->Draw();

	return true;
}

