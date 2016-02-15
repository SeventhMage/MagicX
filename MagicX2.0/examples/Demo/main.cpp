#include "mx.h"
#include "generator.h"


using namespace mx;


const int FRAMES_PER_SECOND = 50;      ///< FPS:50
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	CPlane3 plane(CVector3(1.0f, 0, 0), CVector3(0, 1.0f, 0), CVector3(0, 0, 1.0f));

	IDevice *device = CreateDevice(100, 50, 1024, 720, false);
	IKeyEvent *event = CEventManager::Instance()->GetKeyEvent();
	IRenderer *renderer = device->GetRenderer();
	renderer->Increase();
	//CreateExample_1(renderer);

	CSceneManager *pSceneMgr = CSceneManager::NewInstance();
	IScene *pScene = pSceneMgr->CreateScene();
	CVector3 vDir(0, 0, -1);
	CVector3 vUp(0, 1, 0);
	//vUp.rotateYZBy(DEG_TO_RAD(30.0f));
	//vDir.rotateYZBy(DEG_TO_RAD(30.0f));
	ICamera *pCamera = pSceneMgr->CreateCamera(CVector3(0, 40, 40), vDir, vUp, PI / 2, 1.0f * device->GetWidth() / device->GetHeight(), 1.0f, 5000.0f);
	pScene->SetupCamera(pCamera);
	ISkyBox *pSkyBox = pSceneMgr->CreateSkyBox(renderer, "texture/front.tga", "texture/back.tga", "texture/left.tga", "texture/right.tga", "texture/top.tga", "texture/cloud.tga", 500);
	pScene->SetupSkyBox(pSkyBox);
	ITerrain *pTerrain = pSceneMgr->CreateRandomTerrain(renderer, 256);
	pScene->SetupTerrain(pTerrain);
	
	CMeshManager meshMgr;
	IMesh *mesh = (IMesh *)meshMgr.LoadResource("plg/house.plg");
	CMeshNodeManager meshNodeMgr(renderer);
	CMeshNode *pMeshNode = meshNodeMgr.CreateMeshNode(mesh);
	//pMeshNode->SetPosition(CVector3(100, 100, 100));
	pScene->AddSceneNode(pMeshNode);
	//CVector3 vDir(0, 0, -1);
	//CVector3 vUp(0, 1, 0);	
	vUp.rotateYZBy(DEG_TO_RAD(30.0f));
	vDir.rotateYZBy(DEG_TO_RAD(30.0f));

	ICamera *pFocusCam = pSceneMgr->CreateCamera(40.0f, pMeshNode, vDir, vUp, PI * 0.5f, 1.0f * device->GetWidth() / device->GetHeight(), 1.0f, 1000.0f);
	//pScene->SetupCamera(pFocusCam);
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

			ICamera *pCamera = pScene->GetCamera();
			if (event->IsPress(EKP_MOUSE_LBUTTON) || event->IsPress(EKP_MOUSE_RBUTTON))
			{
				if (event->IsPress(EKP_MOUSE_LBUTTON) && event->IsPress(EKP_MOUSE_RBUTTON))
				{
					CVector3 dir = pCamera->GetDirection();
					CVector3 move = dir.normalize() * float(currentX - lastX) * 0.1f;
					CVector3 pos = pCamera->GetPosition();
					pos += move;
					pCamera->SetPosition(pos);
					//pCamera->SetDistance(float(currentX - lastX) * 0.1f);

				}
				else
				{
					CVector3 xAxis(1, 0, 0);
					CVector3 vYRot(0, 1.0f, 0);
					/*if (pCamera->GetFocus())
						vYRot.y = pCamera->GetFocus()->GetPosition().y - 1.0f;*/
					xAxis.rotateXZBy(rotY, vYRot);

					CVector3 pos = pCamera->GetPosition();
					CVector3 dir = pCamera->GetDirection();
					CVector3 up = pCamera->GetUp();
					pos.rotateXZBy(rotY, vYRot);
					dir.rotateXZBy(rotY, vYRot);
					up.rotateXZBy(rotY, vYRot);

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
	CEventManager::DeleteInstance();
	CSceneManager::DeleteInstance();
	DestroyDevice(device);
	renderer->Decrease();
	return 0;
}