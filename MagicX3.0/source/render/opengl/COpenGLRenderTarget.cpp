#include "COpenGLRenderTarget.h"
#include "GLDebug.h"
#include "mxDef.h"

#include <string.h>

namespace mx
{
	namespace render
	{
		COpenGLRenderTarget::COpenGLRenderTarget(int renderTargetFlag, int width, int height)
			:m_iWidth(width), m_iHeight(height), m_fbo(0)
		{
			memset(m_Texture, 0, sizeof(m_Texture));
			if (renderTargetFlag != 0)
			{
				GLDebug(glGenFramebuffers(1, &m_fbo));
				if (renderTargetFlag & ERTF_COLOR_TEXTURE)
				{
					m_Texture[ETF_COLOR] = new COpenGLTexture();
					m_Texture[ETF_COLOR]->Create2D(GL_RGBA, m_iWidth, m_iHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					//GLDebug(glBindTexture(GL_TEXTURE_2D, m_Texture[ETF_COLOR]->GetHandle()));
					m_Texture[ETF_COLOR]->Bind(0);
					GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
					GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture[ETF_COLOR]->GetHandle(), 0));
					m_Texture[ETF_COLOR]->UnBind();
				}
				if (renderTargetFlag & ERTF_DEPTH_TEXTURE)
				{
					m_Texture[ETF_DEPTH] = new COpenGLTexture();
					m_Texture[ETF_DEPTH]->CreateDepth(m_iWidth, m_iHeight);
					GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
					GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Texture[ETF_DEPTH]->GetHandle(), 0));
				}
				GLCheckFBOStatus(GL_FRAMEBUFFER);
			}
		}
		COpenGLRenderTarget::~COpenGLRenderTarget()
		{
			for (int i = 0; i < ETF_NUM; ++i)
			{
				SAFE_DEL(m_Texture[i]);
			}

			glDeleteFramebuffers(1, &m_fbo);
		}
		void COpenGLRenderTarget::BeginTarget()
		{
			GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
			GLDebug(glViewport(0, 0, m_iWidth, m_iHeight));
			GLDebug(glClearDepth(1.0f));
			GLDebug(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
		}
		void COpenGLRenderTarget::EndTarget()
		{
			GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, 0));
		}
		ITexture * COpenGLRenderTarget::GetBindTexture() const
		{
			return m_Texture[ETF_COLOR];
		}
		ITexture * COpenGLRenderTarget::GetDepthTexture() const
		{
			return m_Texture[ETF_DEPTH];
		}
	}
}