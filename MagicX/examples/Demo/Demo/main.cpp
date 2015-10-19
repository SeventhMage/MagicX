#include <iostream>
#include "mx.h"
#include "IDevice.h"
#include "driver/CMXRenderDriver.h"
#include "IRenderableObject.h"
#include "IBufferObject.h"
#include "glew/gl/glew.h"
#include "ERender.h"
#include "CFileStream.h"

using namespace mx::driver;
using namespace mx::io;

int main(int argc, char *argv[])
{
	CDriver *driver = CDriver::NewInstance();

	IDevice *device = driver->CreateDevice(800, 600);
	CMXRenderDriver *renderDriver = (CMXRenderDriver *)device->GetDeviceDriver(device::DDT_RENDERER);
	if (renderDriver)
	{
		IRenderer *renderer = renderDriver->GetRenderer();
		float triangle[9] = {
			-0.5f, -0.5f, 0,
			0.5f, -0.5f, 0,
			0, 0.5f, 0,
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
				}
			}
			buffer->Begin();
			buffer->CreateVertexBuffer(renderableObject, triangle, sizeof(triangle), 0, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
			buffer->EnableVertexAttrib(VAI_VERTEX, 3/*sizeof(triangle)*/, RVT_FLOAT, 0);
			buffer->End();
		}
		
		renderer->Render();


	}
	
	driver->Run();

	CDriver::DeleteInstance();
	return 0;
}