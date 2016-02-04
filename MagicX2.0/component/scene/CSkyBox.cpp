#include "CSkyBox.h"
#include "render/IRenderableObject.h"
#include "render/IShaderProgram.h"
#include "render/ERender.h"

namespace mx
{
	namespace scene
	{
		CSkyBox::CSkyBox(render::IRenderer *renderer, float r)
			:m_pRenderer(renderer)
			, m_pTexture(NULL)
			,m_pGPUBuffer(NULL)
			, m_pRenderableObject(NULL)
			, m_fRadius(r)
		{
			m_pBoxData = new float[108];
			float vertex[] = {
				//front
				-r, r, r,
				-r, -r, r,
				r, r, r,

				r, r, r,
				-r, -r, r,
				r, -r, r,

				//back
				r, r, -r,
				r, -r, -r,
				-r, r, -r,

				-r, r, -r,
				r, -r, -r,
				-r, -r, -r,

				//left
				-r, r, -r,
				-r, -r, -r,
				-r, r, r,

				-r, r, r,
				-r, -r, -r,
				-r, -r, r,

				//right
				r, r, r,
				r, -r, r,
				r, r, -r,

				r, r, -r,
				r, -r, r,
				r, -r, -r,

				//top
				-r, r, -r,
				-r, r, r,
				r, r, -r,

				r, r, -r,
				-r, r, r,
				r, r, r,

				//bottom
				-r, -r, r,
				-r, -r, -r,
				r, -r, r,

				r, -r, r,
				-r, -r, -r,
				r, -r, -r,
			};

			float fRadius = 1.0f;
			float vertexs[] = {
				fRadius, -fRadius, fRadius,
				fRadius, fRadius, fRadius,
				-fRadius, fRadius, fRadius,
				-fRadius, fRadius, fRadius,
				-fRadius, -fRadius, fRadius,
				fRadius, -fRadius, fRadius,

				fRadius, -fRadius, -fRadius,
				-fRadius, -fRadius, -fRadius,
				-fRadius, fRadius, -fRadius,
				-fRadius, fRadius, -fRadius,
				fRadius, fRadius, -fRadius,
				fRadius, -fRadius, -fRadius,

				-fRadius, fRadius, fRadius,
				-fRadius, fRadius, -fRadius,
				-fRadius, -fRadius, -fRadius,
				-fRadius, fRadius, fRadius,
				-fRadius, -fRadius, -fRadius,
				-fRadius, -fRadius, fRadius,

				fRadius, -fRadius, -fRadius,
				fRadius, fRadius, -fRadius,
				fRadius, fRadius, -fRadius,
				fRadius, fRadius, fRadius,
				fRadius, -fRadius, fRadius,
				fRadius, -fRadius, -fRadius,

				fRadius, fRadius, fRadius,
				fRadius, fRadius, -fRadius,
				fRadius, fRadius, -fRadius,
				fRadius, fRadius, -fRadius,
				-fRadius, fRadius, -fRadius,
				-fRadius, fRadius, fRadius,

				-fRadius, -fRadius, -fRadius,
				fRadius, -fRadius, -fRadius,
				fRadius, -fRadius, fRadius,
				-fRadius, -fRadius, fRadius,
				-fRadius, -fRadius, -fRadius,
				fRadius, -fRadius, fRadius,

			};
			memcpy(m_pBoxData, vertex, sizeof(float) * 108);			
		}

		CSkyBox::~CSkyBox()
		{
			m_pRenderer->DestroyTexture(m_pTexture);
			m_pRenderer->DestroyGPUBuffer(m_pGPUBuffer);			
			SAFE_DEL_ARRAY(m_pBoxData);
		}

		bool CSkyBox::Create(const char * filename)
		{
			return false;
		}

		bool CSkyBox::Create(const char * front, const char * back, const char * left, const char * right, const char * top, const char * bottom)
		{
			m_pGPUBuffer = m_pRenderer->CreateGPUBuffer();
			if (m_pGPUBuffer)
			{
				m_pRenderableObject = m_pGPUBuffer->CreateRenderableObject();
				if (m_pRenderableObject)
				{
					m_pRenderableObject->Disable(render::RA_CULL_FACE);
					render::IShaderProgram *shaderProgram = m_pRenderableObject->GetShaderProgram();
					if (shaderProgram)
					{
						shaderProgram->Attach("shader/skybox.ver", render::ST_VERTEX);
						shaderProgram->Attach("shader/skybox.frg", render::ST_FRAGMENT);
						shaderProgram->BindAttributeLocation(1, render::VAL_POSITION);
						shaderProgram->Link();

						int iTextureUnit = 0;
						shaderProgram->SetUniform("cubeMap", &iTextureUnit);
						
						m_pGPUBuffer->Begin();
						m_pRenderableObject->CreateVertexBufferObject(m_pBoxData, sizeof(float)* 108, 0, 108, render::GBM_TRIANGLES, render::GBU_DYNAMIC_DRAW);
						m_pGPUBuffer->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
						m_pGPUBuffer->End();
						m_pTexture = m_pRenderer->CreateCubeTexture(front, back, left, right, top, bottom);
						m_pRenderableObject->SetTexture(m_pTexture);
						if (m_pTexture)
							return true;
					}
				}
			}			

			return false;
		}


		void CSkyBox::Update(int elapsedTime, const core::CMatrix4 &mat4MVP)
		{
			static float rotY = .0f;
			if (rotY > 3.1415926)
				rotY = .0f;
			rotY += 0.01f * elapsedTime / 1000;

			core::CMatrix4 mat4Rot;
			mat4Rot.setRotationRadiansRH(0, rotY, 0);
			core::CMatrix4 mat4 = mat4MVP * mat4Rot;
			
			if (m_pRenderableObject)
			{
				render::IShaderProgram *shaderProgram = m_pRenderableObject->GetShaderProgram();
				if (shaderProgram)
				{
					shaderProgram->SetUniform("mvpMatrix", (void *)mat4.m);
				}
			}
		}

		void CSkyBox::RenderImp()
		{

		}

	}
}