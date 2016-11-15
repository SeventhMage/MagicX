#include "CSkyBox.h"
#include "render/IRenderable.h"
#include "render/IShaderProgram.h"
#include "render/ERender.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{
		CSkyBox::CSkyBox(IScene *pScene, float r)			
			: m_pTexture(NULL)			
			, m_pRenderable(NULL)
			, m_fRadius(r)
			, m_pParentScene(pScene)
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

			m_pVAO = RENDERER->CreateVertexArrayObject();
			m_pRenderable = RENDERER->CreateRenderable(m_pVAO->GetRenderList());
		}

		CSkyBox::~CSkyBox()
		{
			RENDERER->DestroyTexture(m_pTexture);
			RENDERER->DestroyVertexArrayObject(m_pVAO);
			SAFE_DEL_ARRAY(m_pBoxData);
		}

		bool CSkyBox::Create(const char * filename)
		{
			return false;
		}

		bool CSkyBox::Create(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back)
		{			
			if (m_pVAO)
			{	
				m_pVAO->Bind();
				render::IShaderProgram *pShaderProgram = m_pVAO->GetShaderProgram();
				if (pShaderProgram)
				{
					pShaderProgram->Attach("shader/skybox.vs", render::ST_VERTEX);
					pShaderProgram->Attach("shader/skybox.ps", render::ST_FRAGMENT);
					pShaderProgram->BindAttributeLocation(1, render::VAL_POSITION);
					pShaderProgram->Link();

					int iTextureUnit = 0;
					pShaderProgram->SetUniform("cubeMap", &iTextureUnit);
				}
				if (m_pRenderable)
				{
					m_pRenderable->CreateVertexBufferObject(m_pBoxData, sizeof(float)* 108, 0, 108, render::GBM_TRIANGLES, render::GBU_DYNAMIC_DRAW);
					//m_pRenderableObject->Disable(render::RA_CULL_FACE);
					
					m_pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
					m_pTexture = RENDERER->CreateCubeTexture(right, left, top, bottom, front, back);
					m_pRenderable->SetTexture(0, m_pTexture);
					m_pRenderable->Disable(RA_CULL_FACE);
				}
				m_pVAO->UnBind();
			}			

			return false;
		}


		void CSkyBox::Update(int delta)
		{
			static float rotY = .0f;
			if (rotY > PI * 2)
				rotY = .0f;
			rotY += 0.01f * delta / 1000;
			ICamera *pCamera = m_pParentScene->GetCamera();
			if (pCamera)
			{
				math::CMatrix4 vpMat4 = pCamera->GetViewProjectionMatrix();		
				m_modelMatr4.SetRotationRadiansRH(0, rotY, 0);
				math::CMatrix4 mat4 = m_modelMatr4 * vpMat4;

				if (m_pVAO)
				{
					render::IShaderProgram *shaderProgram = m_pVAO->GetShaderProgram();
					if (shaderProgram)
					{
						shaderProgram->SetUniform("mvpMatrix", (void *)mat4.m);
					}
				}
				m_pRenderable->SumbitToRenderList();
			}			 			
		}

		void CSkyBox::Render()
		{
			m_pVAO->Render();
		}

	}
}