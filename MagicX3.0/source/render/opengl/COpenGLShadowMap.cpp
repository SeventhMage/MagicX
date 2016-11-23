#include "COpenGLShadowMap.h"
#include "GLDebug.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		int g_width = 0, g_height = 0;
		COpenGLShadowMap::COpenGLShadowMap()
		{
			device::IDevice *pDevice = DEVICEMGR->GetDevice();
			if (pDevice)
			{
				g_width = pDevice->GetWindowWidth();
				g_height = pDevice->GetWindowWidth();

				GLDebug(glGenTextures(1, &m_hDepthTexture));
				GLDebug(glBindTexture(GL_TEXTURE_2D, m_hDepthTexture));
				GLDebug(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, pDevice->GetWindowWidth(), 
					pDevice->GetWindowHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				GLDebug(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
				GLDebug(glBindTexture(GL_TEXTURE_2D, 0));
				GLDebug(glGenFramebuffers(1, &m_hDepthFBO));
				GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_hDepthFBO));

				

				/*	GLDebug(glGenRenderbuffers(1, &m_hDepthRBO));
					GLDebug(glBindRenderbuffer(GL_RENDERBUFFER, m_hDepthRBO));
					GLDebug(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pDevice->GetWindowWidth(), pDevice->GetWindowHeight()));

					GLDebug(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_hDepthRBO));*/

				GLDebug(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_hDepthTexture, 0));

				// Disable color rendering as there are no color attachments
				GLDebug(glDrawBuffer(GL_NONE));

				GLCheckFBOStatus(GL_FRAMEBUFFER);

				GLDebug(glBindRenderbuffer(GL_RENDERBUFFER, 0));
				GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, 0));

				m_pShaderProgram = RENDERER->CreateShaderProgram();
				m_pShaderProgram->Attach("shader/shadow.vs", ST_VERTEX);
				m_pShaderProgram->Attach("shader/shadow.ps", ST_FRAGMENT);
				m_pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				m_pShaderProgram->Link();
			}
		}

		COpenGLShadowMap::~COpenGLShadowMap()
		{
			GLDebug(glDeleteRenderbuffers(1, &m_hDepthFBO));
			GLDebug(glDeleteFramebuffers(1, &m_hDepthFBO));
		}

		void COpenGLShadowMap::Render()
		{
			IScene *pScene = SCENEMGR->GetCurrentScene();
			if (pScene)
			{
				ILight *pLight = pScene->GetLight(0);
				CMatrix4 lightViewMat;
				CVector3 pos = ((CPointLight *)pLight)->GetPosition();
				lightViewMat.BuildCameraLookAtMatrix(pos, -pos, CVector3(0, 1, 0));
				CMatrix4 lightProMat;
				lightProMat.BuildProjectionMatrixPerspectiveFovRH(PI / 3.f, 1.f * g_width / g_height, 1.f, 1000.f);



				CMatrix4 vpMat = lightViewMat * lightProMat;

				m_pShaderProgram->SetUniform("mvpMatrix", vpMat.m);
			}

			GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_hDepthFBO));
			GLDebug(glDrawBuffer(GL_NONE));
			GLCheckFBOStatus(GL_FRAMEBUFFER);
			GLDebug(glViewport(0, 0, g_width, g_height));

			GLDebug(glClearDepth(1.0f));
			GLDebug(glClear(GL_DEPTH_BUFFER_BIT));
			
			GLDebug(glEnable(GL_POLYGON_OFFSET_FILL));
			GLDebug(glPolygonOffset(2.0f, 4.0f));
			RENDERER->Render();
			GLDebug(glDisable(GL_POLYGON_OFFSET_FILL));

			GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			
			//glDrawBuffer(GL_FRONT_LEFT);
		}

	}
}