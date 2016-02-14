#include "generator.h"

namespace mx
{
	void CreateExample_1(IRenderer *renderer)
	{
		typedef struct
		{
			float x, y, z;
			float u, v;
		}Vertex;

		Vertex pyramid[9] = {
			{ -5.0f, -5.0f, 5.0f, 0, 1.0f },
			{ 5.0f, -5.0f, 5.0f, 1.0f, 1.0f },
			{ 0, 5.0f, 0, 0.5f, 0 },

			{ 5.0f, -5.0f, 5.0f, 0.0f, 1.0f },
			{ 0, -5.0f, -5.0f, 1.0f, 1.0f },
			{ 0, 5.0f, 0, 0.5f, 0 },

			{ 0, -5.0f, -5.0f, 0.0f, 1.0f },
			{ -5.0f, -5.0f, 5.0f, 1.0f, 1.0f },
			{ 0, 5.0f, 0, 0.5f, 0 },
		};

		uint indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

		IGPUBuffer *buffer = renderer->CreateGPUBuffer();

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

					float vColor[] = { 1, 1, 1, 1 };
					shaderProgram->SetUniform("vColor", vColor);
					CMatrix4 mat4;
					//mat4.buildProjectionMatrixOrthoRH(20, 20, 10, -10);

					CMatrix4 projectMat4;
					projectMat4.BuildProjectionMatrixPerspectiveFovRH(PI / 2.0f, 1.0f * 600 / 800, 1, 100.0f);
					CMatrix4 viewMat4;
					viewMat4.BuildCameraLookAtMatrix(CVector3(0, 0, 0), CVector3(0, 0, -1), CVector3(0, 1, 0));
					CMatrix4 modelMat4;
					modelMat4.SetTranslation(CVector3(0, 0, -20.0f));

					CMatrix4 mvpMat4 = projectMat4 * viewMat4 * modelMat4;

					shaderProgram->SetUniform("mvpMatrix", mvpMat4.m);
				}
				buffer->Begin();
				renderableObject->CreateVertexBufferObject(pyramid, sizeof(pyramid), 0, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				renderableObject->CreateIndexBufferObject(indices, 9, RVT_UINT, 9, GBM_TRIANGLES, GBU_DYNAMIC_DRAW);
				//buffer->AddVertexData(renderableObject, triangle1, sizeof(triangle1), 0);
				//buffer->AddVertexData(renderableObject, color, sizeof(color), sizeof(triangle));
				//buffer->AddVertexData(renderableObject, texture, sizeof(texture), sizeof(triangle1));
				buffer->EnableVertexAttrib(VAL_POSITION, 4, RVT_FLOAT, sizeof(Vertex), 0);
				//buffer->EnableVertexAttrib(VAI_COLOR, 4, RVT_FLOAT, sizeof(triangle));
				buffer->EnableVertexAttrib(VAL_TEXTURE0, 2, RVT_FLOAT, sizeof(Vertex), sizeof(float)* 3);

				buffer->End();

			}

			ITexture *tex = renderer->CreateTexture("texture/1.tga", TT_2D);
			renderableObject->SetTexture(tex);

		}
	}
}