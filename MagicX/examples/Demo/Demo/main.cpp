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

using namespace mx::driver;
using namespace mx::io;

const int FRAMES_PER_SECOND = 50;      ///< FPS:50
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	CDriver *driver = CDriver::NewInstance();

	IDevice *device = driver->CreateDevice(800, 600);
	CMXRenderDriver *renderDriver = (CMXRenderDriver *)device->GetDeviceDriver(device::DDT_RENDERER);
	if (renderDriver)
	{
		IRenderer *renderer = renderDriver->GetRenderer();
		float triangle[9] = {
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

		IGPUBuffer *buffer = renderer->CreateGPUBuffer(0);
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
					shaderProgram->Link();
					int iTextureUnit = 0;
					shaderProgram->SetUniform("textureUnit0", &iTextureUnit);
					CMatrix4 mat4;
					mat4.buildProjectionMatrixOrtho(2, 2, -1, 1);
					
					shaderProgram->SetUniform("mvpMatrix", mat4.m);
				}
			}
			buffer->Begin();
			buffer->CreateVertexBuffer(renderableObject, NULL, sizeof(triangle) + sizeof(texture), 0, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			buffer->AddVertexData(renderableObject, triangle, sizeof(triangle), 0);
			//buffer->AddVertexData(renderableObject, color, sizeof(color), sizeof(triangle));
			buffer->AddVertexData(renderableObject, texture, sizeof(texture), sizeof(triangle));
			buffer->EnableVertexAttrib(VAI_VERTEX, 3, RVT_FLOAT, 0);
			//buffer->EnableVertexAttrib(VAI_COLOR, 4, RVT_FLOAT, sizeof(triangle));
			buffer->EnableVertexAttrib(VAI_TEXTURE1, 2, RVT_FLOAT, sizeof(triangle));

			buffer->End();

			ITexture *tex = renderer->CreateTexture("media/1.tga", TT_2D);
			renderableObject->SetTexture(tex);
		}
		
		uint next_game_tick = device->GetSystemRunTime();
		int sleep_time = 0;
		while (device->Run())
		{
			renderer->Render();
			device->SwapBuffers();

			next_game_tick += SKIP_TICKS;
			sleep_time = next_game_tick - GetTickCount();
			if (sleep_time >= 0)
			{
				device->Sleep(sleep_time);
			}			 
		}

	}
	
	//driver->Run();

	CDriver::DeleteInstance();
	return 0;
}