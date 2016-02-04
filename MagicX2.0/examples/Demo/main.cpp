#include "mx.h"
#include "generator.h"

using namespace mx;


const int FRAMES_PER_SECOND = 50;      ///< FPS:50
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	IDevice *device = CreateDevice(100, 50, 1024, 720, false);
	IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
	IRenderer *renderer = device->GetRenderer();
	CMeshManager *pMeshMgr = new CMeshManager(renderer);
	IMesh *mesh = (IMesh *)pMeshMgr->LoadResource("plg/house.plg");		

	//CreateExample_1(renderer);

	CSceneManager *pSceneMgr = new CSceneManager(renderer);
	IScene *pScene = pSceneMgr->CreateScene();

	ICamera *pCamera = pSceneMgr->CreateCamera(CVector3(0, 20, 0), CVector3(0, 0, -1), CVector3(0, 1, 0), PI / 2, 1.0f * device->GetHeight() / device->GetWidth(), 1.0f, 5000.0f);
	pScene->SetupCamera(pCamera);
	ISkyBox *pSkyBox = pSceneMgr->CreateSkyBox("texture/front.tga", "texture/back.tga", "texture/left.tga", "texture/right.tga", "texture/top.tga", "texture/cloud.tga", 500);
	pScene->SetupSkyBox(pSkyBox);
	ITerrain *pTerrain = pSceneMgr->CreateRandomTerrain(128);
	pScene->SetupTerrain(pTerrain);
	

	uint next_game_tick = device->GetSystemRunTime();
	int sleep_time = 0;
	while (device->Run())
	{
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - GetTickCount();
		if (sleep_time >= 0)
		{
			pSceneMgr->Update(next_game_tick);
			if (renderer)
			{
				mesh->rotateXZBy(0.01f);
				mesh->rotateYZBy(0.005f);
				mesh->Update(next_game_tick);
				renderer->Render();
				device->SwapBuffers();
			}
			device->Sleep(sleep_time);
		}

		if (event)
		{
			static int lastX;
			static int lastY;

			int currentX = event->GetMousePositonX();
			int currentY = event->GetMousePositionY();

			float rotY = (currentX - lastX) * 2.0f * PI / device->GetWidth();
			float rotX = (currentY - lastY) * 2.0f * PI / device->GetWidth();

			if (event->IsPress(EKP_MOUSE_LBUTTON))
			{
				if (event->IsPress(EKP_MOUSE_RBUTTON))
				{
					CVector3 dir = pCamera->GetDirection();
					CVector3 move = dir.normalize() * (currentX - lastX) * 0.1f;
					CVector3 pos = pCamera->GetPosition();
					pos += move;
					pCamera->SetPosition(pos);

				}
				else
				{
					CVector3 xAxis(1, 0, 0);
					xAxis.rotateXZBy(rotY);

					CVector3 pos = pCamera->GetPosition();
					CVector3 dir = pCamera->GetDirection();
					CVector3 up = pCamera->GetUp();
					pos.rotateXZBy(rotY);
					dir.rotateXZBy(rotY);
					up.rotateXZBy(rotY);

					/*
					CMatrix4 mat4;
					mat4.setRotationAxisRadians(rotX, xAxis);
					mat4.rotate(pos);
					mat4.rotate(dir);
					mat4.rotate(up);*/


					pCamera->SetPosition(pos);
					pCamera->SetDirection(dir);
					pCamera->SetUp(up);

				}

			}

			renderer->PolygonMeshMode(event->IsPress(EKP_KEYBOARD_N));

			lastX = event->GetMousePositonX();
			lastY = event->GetMousePositionY();
		
			if (event->IsPress(EKP_KEYBOARD_ESC))
			{
				exit(1);
			}
		}
	}

	DestroyDevice(device);
	return 0;
}