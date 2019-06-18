#include "COpenGLRenderTarget.h"
#include "GLDebug.h"
#include "mxDef.h"

#include <string.h>
#include <queue>

namespace mx
{
	namespace render
	{
		static const int MAX_TEXTURE_COUNT = 16;
		COpenGLRenderTarget::COpenGLRenderTarget(int textureCount, int width, int height, bool bHaveDepth)
			:m_iWidth(width), m_iHeight(height), m_fbo(0), m_textureCount(textureCount), m_depthTexture(nullptr)
		{

			GLenum drawBuffers[MAX_TEXTURE_COUNT] = { 0 };
			if (textureCount > 0 || bHaveDepth)
			{
				GLDebug(glGenFramebuffers(1, &m_fbo));
				GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
				for (int i = 0; i < textureCount; ++i)
				{
					ITexture *pTexture = new COpenGLTexture();
					pTexture->Create2D(GL_RGBA8, m_iWidth, m_iHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					pTexture->Bind(0);
					GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, pTexture->GetHandle(), 0));
					pTexture->UnBind();
					m_bindTexture.push_back(pTexture);
					drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
				}
				
				if (bHaveDepth)
				{
					m_depthTexture = new COpenGLTexture();
					m_depthTexture->CreateDepth(m_iWidth, m_iHeight);
					GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture->GetHandle(), 0));
				}

			}
			
			if (textureCount > 0)
			{
				glDrawBuffers(textureCount, drawBuffers);

				GLCheckFBOStatus(GL_FRAMEBUFFER);

				GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			}
			else if (textureCount == 0 && bHaveDepth)
			{
				glDrawBuffer(GL_NONE);
			}
		}
		COpenGLRenderTarget::~COpenGLRenderTarget()
		{
			for (auto texture : m_bindTexture)
			{
				SAFE_DEL(texture);
			}
			SAFE_DEL(m_depthTexture);

			glDeleteFramebuffers(1, &m_fbo);
		}
		void COpenGLRenderTarget::BeginTarget()
		{
			GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
			GLDebug(glViewport(0, 0, m_iWidth, m_iHeight));
			GLDebug(glClearDepth(1.0f));
			GLDebug(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
			if (m_textureCount == 0 && m_depthTexture != nullptr)
			{
				GLDebug(glEnable(GL_POLYGON_OFFSET_FILL));
				GLDebug(glPolygonOffset(2.0f, 4.0f))
			}
		}
		void COpenGLRenderTarget::EndTarget()
		{
			GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			if (m_textureCount == 0 && m_depthTexture != nullptr)
			{
				GLDebug(glDisable(GL_POLYGON_OFFSET_FILL));
			}
		}
		ITexture * COpenGLRenderTarget::GetBindTexture(int index) const
		{
			return m_bindTexture[index];
		}
		ITexture * COpenGLRenderTarget::GetDepthTexture() const
		{
			return m_depthTexture;
		}

		mx::render::ITexture * COpenGLRenderTarget::GetTexture(int index) const
		{
			if (index < 0)
				return GetDepthTexture();
			return GetBindTexture(index);
		}

	}
}