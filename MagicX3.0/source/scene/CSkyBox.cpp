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

			AddRenderPhase(3, 11);
		}

		CSkyBox::~CSkyBox()
		{
			RENDERER->DestroyTexture(m_pTexture);
			SAFE_DEL_ARRAY(m_pBoxData);
		}

		bool CSkyBox::Create(const char * filename)
		{
			return false;
		}

		bool CSkyBox::Create(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back)
		{			
			for (auto renderable : m_vecRenderables)
			{
				IVertexArrayObject *pVAO = renderable->GetVertexArrayObject();
				if (pVAO)
				{
					pVAO->Bind();

					if (renderable)
					{
						int iTextureUnit = 0;
						renderable->SetUniform("cubeMap", &iTextureUnit);

						renderable->CreateVertexBufferObject(m_pBoxData, sizeof(float) * 108, 0, 108, render::GBM_TRIANGLES, render::GBU_DYNAMIC_DRAW);
						//m_pRenderableObject->Disable(render::RA_CULL_FACE);

						pVAO->EnableVertexAttrib(render::VAL_POSITION, 3, render::RVT_FLOAT, 0, 0);
						m_pTexture = RENDERER->CreateCubeTexture(right, left, top, bottom, front, back);
						renderable->SetTexture(0, m_pTexture);
						renderable->Disable(RA_CULL_FACE);
					}
					pVAO->UnBind();
				}
			}
		
			m_pParentScene->GetRootNode()->AddChild(this);
			return true;
		}


		void CSkyBox::UpdateImp(int delta)
		{
			CEntity::UpdateImp(delta);
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
				for (auto renderable : m_vecRenderables)
				{
					renderable->SetUniform("mvpMatrix", (void *)mat4.m);
				}
			}			 			
		}
	}
}