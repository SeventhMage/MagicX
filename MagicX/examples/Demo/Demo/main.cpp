#include <iostream>
#include "mx.h"
#include "IDevice.h"
#include "driver/CMXRenderDriver.h"
#include "IRenderableObject.h"
#include "IBufferObject.h"
#include "glew/gl/glew.h"
#include "ERender.h"
#include "CFileStream.h"
#include "CDeviceManager.h"
#include "SVertexAttribute.h"
#include "common/mxMath.h"
#include "CSceneManager.h"
#include "IScene.h"
#include "ICameraSceneNode.h"
#include "ISkyBoxSceneNode.h"
#include "ITerrainSceneNode.h"
#include "IKeyEvent.h"
#include "CEventManager.h"
#include "common/mxMath.h"
#include "common/mxDef.h"

using namespace mx::driver;
using namespace mx::io;
using namespace mx::scene;

const int FRAMES_PER_SECOND = 50;      ///< FPS:50
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	CDriver *driver = CDriver::NewInstance();

	IDevice *device = driver->CreateDevice(1366, 768);
	CMXRenderDriver *renderDriver = (CMXRenderDriver *)device->GetDeviceDriver(device::DDT_RENDERER);
	if (renderDriver)
	{
		IRenderer *renderer = renderDriver->GetRenderer();
		float triangle[] = {
			-1.f, -1.f, 0,
			0, 1.0f,
			.7f, -.7f, 0,
			1.0f, 1.0f,
			0, .5f, 0,
			0.5f, 0,
		};

		float triangle1[] = {
			-1.f, -1.f, 0,
			.7f, -.7f, 0,
			0, .5f, 0,
		};

		float color[12] = {
			1.0f, 0, 0, 1.0f,
			0, 1.0f, 0, 1.0f,
			0, 0, 1.0f, 1.0f
		};
		
		float texture[] = {
			0, 1.0f,
			1.0f, 1.0f,
			0.5f, .0f,
			
		};

		float texture1[] = {
			0, 0,
			1, 0,
			0.5, 1
		};
		
		float texture2[] = {
			0, 0.5f,
			.5f, .5f,
			0.5f, .0f
		};

		typedef struct
		{
			float x, y, z, w;			
			float u, v;
		}Vertex;

		Vertex pyramid[9] = {
			{-5.0f, -5.0f, 5.0f, 1.0f, 0, 1.0f},
			{5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f},
			{0, 5.0f, 0, 1.0f, 0.5f, 0},

			{ 5.0f, -5.0f, 5.0f, 1.0f, 0.0f, 1.0f },
			{0, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f},
			{ 0, 5.0f, 0, 1.0f, 0.5f, 0 },

			{ 0, -5.0f, -5.0f, 1.0f, 0.0f, 1.0f },
			{ -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f },
			{ 0, 5.0f, 0, 1.0f, 0.5f, 0 },
		};
		
		uint indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
		/*
		IGPUBuffer *buffer = renderer->CreateGPUBuffer(sizeof(Vertex));
		
		if (buffer)
		{
			
			IRenderableObject *renderableObject = buffer->CreateRenderableObject();
			if (renderableObject)
			{
				IShaderProgram *shaderProgram = renderableObject->GetShaderProgram();
				if (shaderProgram)
				{
					shaderProgram->Attach("shader/test.ver", ST_VERTEX);
					shaderProgram->Attach("shader/test.frg", ST_FRAGMENT);
					shaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_TEXTURE0);
					shaderProgram->Link();
					int iTextureUnit = 0;
					shaderProgram->SetUniform("textureUnit0", &iTextureUnit);

					CMatrix4 mat4;
					mat4.buildProjectionMatrixOrtho(20, 20, 10, -10);

					CMatrix4 projectMat4;										
					projectMat4.buildProjectionMatrixPerspectiveFov(core::PI / 2.0f, 1.0f * device->GetHeight() / device->GetWidth(), 1, 100.0f);
					CMatrix4 viewMat4;
					viewMat4.buildCameraLookAtMatrix(CVector3(0, 0, 0), CVector3(0, 0, -1), CVector3(0, 1, 0));
					CMatrix4 modelMat4;
					modelMat4.setTranslation(CVector3(0, 0, -20.0f));
	
					CMatrix4 mvpMat4 = projectMat4 * viewMat4 * modelMat4;
					
					shaderProgram->SetUniform("mvpMatrix", mvpMat4.m);
				}
			}
			buffer->Begin();
			buffer->CreateVertexBuffer(renderableObject, pyramid, sizeof(pyramid), 0, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			buffer->CreateIndexBuffer(renderableObject, indices, 9, RVT_UINT, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			//buffer->AddVertexData(renderableObject, triangle1, sizeof(triangle1), 0);
			//buffer->AddVertexData(renderableObject, color, sizeof(color), sizeof(triangle));
			//buffer->AddVertexData(renderableObject, texture, sizeof(texture), sizeof(triangle1));
			buffer->EnableVertexAttrib(VAL_POSITION, 4, RVT_FLOAT, 0);
			//buffer->EnableVertexAttrib(VAI_COLOR, 4, RVT_FLOAT, sizeof(triangle));
			buffer->EnableVertexAttrib(VAL_TEXTURE0, 2, RVT_FLOAT, sizeof(float) * 4);

			buffer->End();

			ITexture *tex = renderer->CreateTexture("texture/1.tga", TT_2D);
			renderableObject->SetTexture(tex);
			*/
			
			CSceneManager sceneMgr(renderer);
			IScene *scene = sceneMgr.CreateScene();
			ICameraSceneNode *camera = sceneMgr.CreateCamera(CVector3(0, 50, 0), CVector3(0, 0, -1), CVector3(0, 1, 0), core::PI / 3.0f, 1.0f * device->GetHeight() / device->GetWidth(), 1, 5000.0f);
			scene->SetupCamera(camera);

			ISkyBoxSceneNode *skybox = sceneMgr.CreateSkyBox("texture/front.tga", "texture/back.tga", "texture/left.tga", "texture/right.tga", "texture/top.tga", "texture/cloud.tga", 500);
			scene->SetupSkyBox(skybox);

			ITerrainSceneNode *terrain = sceneMgr.CreateRandomTerrain(256);
			scene->SetupTerrain(terrain);
			
			
			IKeyEvent *keyEvent = CEventManager::Instance()->GetKeyEvent();


			uint next_game_tick = device->GetSystemRunTime();
			int sleep_time = 0;
			
			while (device->Run())
			{		
				if (keyEvent)
				{
					static int lastX;
					static int lastY;

					int currentX = keyEvent->GetMousePositonX();
					int currentY = keyEvent->GetMousePositionY();

					float rotY = (currentX - lastX) * 2.0f * core::PI / device->GetWidth();
					float rotX = (currentY - lastY) * 2.0f * core::PI / device->GetWidth();

					if (keyEvent->IsPress(EKP_MOUSE_LBUTTON))
					{					
						if (keyEvent->IsPress(EKP_MOUSE_RBUTTON))
						{
							CVector3 dir = camera->GetDirection();
							CVector3 move = (currentX - lastX) * 0.1f * dir.normalize();
							CVector3 pos = camera->GetPosition();
							pos += move;
							camera->SetPosition(pos);
							
						}
						else
						{							
							CVector3 xAxis(1, 0, 0);
							xAxis.rotateXZBy(rotY);

							CVector3 pos = camera->GetPosition();
							CVector3 dir = camera->GetDirection();
							CVector3 up = camera->GetUp();
							pos.rotateXZBy(rotY);
							dir.rotateXZBy(rotY);
							up.rotateXZBy(rotY);

 /*
 							CMatrix4 mat4;
 							mat4.setRotationAxisRadians(rotX, xAxis);
 							mat4.rotate(pos);
 							mat4.rotate(dir);
 							mat4.rotate(up);*/

							
							camera->SetPosition(pos);
							camera->SetDirection(dir);
							camera->SetUp(up);
							
						}
			
					}
				
					renderer->PolygonMeshMode(keyEvent->IsPress(EKP_KEYBOARD_N));

					lastX = keyEvent->GetMousePositonX();
					lastY = keyEvent->GetMousePositionY();
				}

				/*
				for (int i = 0; i < 9; ++i)
				{
					CVector3 vec3 = CVector3(pyramid[i].x, pyramid[i].y, pyramid[i].z);
					vec3.rotateXZBy(0.01f);
					
					pyramid[i].x = vec3.x;
					pyramid[i].y = vec3.y;
					pyramid[i].z = vec3.z;
				}
				buffer->AddVertexData(renderableObject, pyramid, sizeof(pyramid), 0);
			*/

				next_game_tick += SKIP_TICKS;
				sleep_time = next_game_tick - GetTickCount();
				if (sleep_time >= 0)
				{
					device->Sleep(sleep_time);
				}

				sceneMgr.Update(next_game_tick);
				sceneMgr.Render();
				//renderer->Render();
				device->SwapBuffers();
			}
		}

	

	//}
	
	//driver->Run();

	CDriver::DeleteInstance();
	return 0;
}