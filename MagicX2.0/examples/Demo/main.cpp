#include "mx.h"

using namespace mx;


const int FRAMES_PER_SECOND = 50;      ///< FPS:50
const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

int main(int argc, char *argv[])
{
	IDevice *device = CreateDevice(100, 100, 800, 600, false);

	IRenderer *renderer = device->GetRenderer();
	IMesh *mesh = CResourceManager::Instance()->LoadResource("plg/cube1.plg");

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
		
	IGPUBuffer *buffer = renderer->CreateGPUBuffer(sizeof(Vertex));
			
	if (buffer)
	{

		IRenderableObject *renderableObject = buffer->CreateRenderableObject();
		if (renderableObject)
		{
			IShaderProgram *shaderProgram = renderableObject->GetShaderProgram();
			if (shaderProgram)
			{
				//shaderProgram->Attach("shader/test.ver", ST_VERTEX);
				//shaderProgram->Attach("shader/test.frg", ST_FRAGMENT);
				//shaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_TEXTURE0);
				//shaderProgram->Link();

				shaderProgram->CreateStandShader(ESS_SHADER_TEXTURE_MODULATE);

				int iTextureUnit = 0;
				shaderProgram->SetUniform("textureUnit0", &iTextureUnit);

				float vColor[] = {1, 1, 1, 1};
				shaderProgram->SetUniform("vColor", vColor);
				CMatrix4 mat4;
				//mat4.buildProjectionMatrixOrthoRH(20, 20, 10, -10);

				CMatrix4 projectMat4;
				projectMat4.buildProjectionMatrixPerspectiveFovRH(PI / 2.0f, 1.0f * device->GetHeight() / device->GetWidth(), 1, 100.0f);
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
		buffer->EnableVertexAttrib(VAL_TEXTURE0, 2, RVT_FLOAT, sizeof(float)* 4);

		buffer->End();

		ITexture *tex = renderer->CreateTexture("texture/1.tga", TT_2D);
		renderableObject->SetTexture(tex);

	}

	uint next_game_tick = device->GetSystemRunTime();
	int sleep_time = 0;
	while (device->Run())
	{
		next_game_tick += SKIP_TICKS;
		sleep_time = next_game_tick - GetTickCount();
		if (sleep_time >= 0)
		{
			if (renderer)
			{
				renderer->DrawLine(CVector3(0, 0, 0), CVector3(100, 100, 100));
				
				if (mesh)
				{
					renderer->DrawMesh(mesh);
				}
				renderer->Render();
			}
			device->Sleep(sleep_time);
		}

		device->SwapBuffers();
	}

	DestroyDevice(device);
	return 0;
}