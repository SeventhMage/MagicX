#include "COpenGLRenderTarget.h"
#include "GLDebug.h"
#include "mxDef.h"

#include <string.h>
#include <queue>

namespace mx
{
	namespace render
	{
		COpenGLRenderTarget::COpenGLRenderTarget(int renderTargetFlag, int width, int height)
			:m_iWidth(width), m_iHeight(height), m_fbo(0), m_renderTargetFlag(renderTargetFlag)
		{
			if (renderTargetFlag != 0)
			{
				GLDebug(glGenFramebuffers(1, &m_fbo));
				GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));

				GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
				int textureCount = 0;
				if (renderTargetFlag & ERTF_COLOR_TEXTURE)
				{
					m_Texture[ERTF_COLOR_TEXTURE] = new COpenGLTexture();
					m_Texture[ERTF_COLOR_TEXTURE]->Create2D(GL_RGBA32F, m_iWidth, m_iHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					m_Texture[ERTF_COLOR_TEXTURE]->Bind(0);
					GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, drawBuffers[textureCount++], GL_TEXTURE_2D, m_Texture[ERTF_COLOR_TEXTURE]->GetHandle(), 0));
					m_Texture[ERTF_COLOR_TEXTURE]->UnBind();
				}

				if (renderTargetFlag & ERTF_POSITION_TEXTURE)
				{
					m_Texture[ERTF_POSITION_TEXTURE] = new COpenGLTexture();
					m_Texture[ERTF_POSITION_TEXTURE]->Create2D(GL_RGBA32F, m_iWidth, m_iHeight, GL_RGBA,  GL_UNSIGNED_BYTE, nullptr);
					m_Texture[ERTF_POSITION_TEXTURE]->Bind(0);
					GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, drawBuffers[textureCount++], GL_TEXTURE_2D, m_Texture[ERTF_POSITION_TEXTURE]->GetHandle(), 0));
					m_Texture[ERTF_POSITION_TEXTURE]->UnBind();
				}

				if (renderTargetFlag & ERTF_NORMAL_TEXTURE)
				{
					m_Texture[ERTF_NORMAL_TEXTURE] = new COpenGLTexture();
					m_Texture[ERTF_NORMAL_TEXTURE]->Create2D(GL_RGBA32F, m_iWidth, m_iHeight, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
					m_Texture[ERTF_NORMAL_TEXTURE]->Bind(0);
					GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, drawBuffers[textureCount++], GL_TEXTURE_2D, m_Texture[ERTF_NORMAL_TEXTURE]->GetHandle(), 0));
					m_Texture[ERTF_NORMAL_TEXTURE]->UnBind();
				}

				if (renderTargetFlag & ERTF_DEPTH_TEXTURE)
				{
					m_Texture[ERTF_DEPTH_TEXTURE] = new COpenGLTexture();
					m_Texture[ERTF_DEPTH_TEXTURE]->CreateDepth(m_iWidth, m_iHeight);
					GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
					GLDebug(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Texture[ERTF_DEPTH_TEXTURE]->GetHandle(), 0));
				}				
				
				if (textureCount > 0)
				{
					glDrawBuffers(textureCount, drawBuffers);
				}
				else
				{
					glDrawBuffer(GL_NONE);
				}
				GLCheckFBOStatus(GL_FRAMEBUFFER);

				GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			}
		}
		COpenGLRenderTarget::~COpenGLRenderTarget()
		{
			for (auto it : m_Texture)
			{
				SAFE_DEL(it.second);
			}

			glDeleteFramebuffers(1, &m_fbo);
		}
		void COpenGLRenderTarget::BeginTarget()
		{
			GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, m_fbo));
			GLDebug(glViewport(0, 0, m_iWidth, m_iHeight));
			GLDebug(glClearDepth(1.0f));
			GLDebug(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
			if (m_renderTargetFlag == ERTF_DEPTH_TEXTURE)
			{
				GLDebug(glEnable(GL_POLYGON_OFFSET_FILL));
				GLDebug(glPolygonOffset(2.0f, 4.0f))
			}
		}
		void COpenGLRenderTarget::EndTarget()
		{
			GLDebug(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			if (m_renderTargetFlag == ERTF_DEPTH_TEXTURE)
			{
				GLDebug(glDisable(GL_POLYGON_OFFSET_FILL));
			}
		}
		ITexture * COpenGLRenderTarget::GetBindTexture() const
		{
			return nullptr;
			//return m_Texture[ERTF_COLOR_TEXTURE];
		}
		ITexture * COpenGLRenderTarget::GetDepthTexture() const
		{
			return nullptr;
			//return m_Texture[ERTF_DEPTH_TEXTURE];
		}

		mx::render::ITexture * COpenGLRenderTarget::GetTexture(int flag) const
		{
			auto it = m_Texture.find(flag);
			if (it != m_Texture.end())
			{
				return it->second;
			}
			return nullptr;
		}

	}
}