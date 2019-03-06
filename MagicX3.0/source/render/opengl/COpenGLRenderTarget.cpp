#include "COpenGLRenderTarget.h"
#include "GLDebug.h"

namespace mx
{
	namespace render
	{
		COpenGLRenderTarget::COpenGLRenderTarget(int renderTargetFlag, int width, int height)
			:m_iWidth(width), m_iHeight(height), m_bindTexture(nullptr), m_depthTexture(nullptr), m_fbo(0)
		{
			if (renderTargetFlag != 0)
				GLDebug(glGenFramebuffers(1, &m_fbo));
			if (renderTargetFlag & ERTF_BIND_TEXTURE)
			{
				m_bindTexture = new COpenGLTexture();
				m_bindTexture->Create2D(GL_RGBA, m_iWidth, m_iHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				GLDebug(glBindTexture(GL_TEXTURE_2D, m_bindTexture->GetHandle()));
				GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
				GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_bindTexture->GetHandle(), 0));
			}
			if (renderTargetFlag & ERTF_DEPTH_TEXTURE)
			{
				m_depthTexture = new COpenGLTexture();
				m_depthTexture->CreateDepth(m_iWidth, m_iHeight);
				GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
				GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->GetHandle(), 0));
			}
		}
		COpenGLRenderTarget::~COpenGLRenderTarget()
		{
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
			return m_bindTexture;
		}
		ITexture * COpenGLRenderTarget::GetDepthTexture() const
		{
			return m_depthTexture;
		}
	}
}