#include "COpenGLRenderer.h"
#include "glew/gl/glew.h"
#include "COpenGLTexture.h"
#include "COpenGLGPUBuffer.h"
#include "mxDef.h"

namespace mx
{
	namespace render
	{

		COpenGLRenderer::COpenGLRenderer()
		{

		}

		COpenGLRenderer::~COpenGLRenderer()
		{

		}

		void COpenGLRenderer::DrawLine(const core::CVector3 &vFrom, const core::CVector3 &vTo, const SColor &color)
		{
				
		}

		void COpenGLRenderer::DrawImage(const resource::IImage *image, uint uScreenX /* = 0 */, uint uScreenY /* = 0 */)
		{

		}

		void COpenGLRenderer::DrawMesh(const resource::IMesh *pMesh)
		{

		}

		void COpenGLRenderer::AddMesh(resource::IMesh *pMesh)
		{

		}

		void COpenGLRenderer::DrawRenderList()
		{

		}

		void COpenGLRenderer::Render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (uint i = 0; i < m_vecBuffer.size(); ++i)
			{
				if (m_vecBuffer[i])
				{
					m_vecBuffer[i]->Render();
				}
			}
		}

		IGPUBuffer * COpenGLRenderer::CreateGPUBuffer(int stride)
		{
			IGPUBuffer *buffer = new COpenGLGPUBuffer(stride);
			m_vecBuffer.push_back(buffer);
			return buffer;
		}

		void COpenGLRenderer::DestroyGPUBuffer(IGPUBuffer *gpuBuffer)
		{
			for (uint i = 0; i < m_vecBuffer.size(); ++i)
			{
				if (m_vecBuffer[i] == gpuBuffer)
				{
					m_vecBuffer.erase(i + m_vecBuffer.begin());
					SAFE_DEL(gpuBuffer);
				}
			}
		}

		ITexture * COpenGLRenderer::CreateTexture(const char * filename, TextureType texType)
		{
			ITexture *tex = new COpenGLTexture();
			tex->Create(filename, texType);
			return tex;
		}

		ITexture * COpenGLRenderer::CreateCubeTexture(const char * front, const char * back, const char * left, const char * right, const char * top, const char * bottom)
		{
			ITexture *tex = new COpenGLTexture();
			tex->CreateCube(front, back, left, right, top, bottom);
			return tex;
		}

		void COpenGLRenderer::ClearColor(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a);
		}

		void COpenGLRenderer::Clear(uint mask)
		{
			glClear(mask);
		}

		void COpenGLRenderer::Enable(uint cap)
		{
			glEnable(cap);
		}

		void COpenGLRenderer::Disable(uint cap)
		{
			glDisable(cap);
		}

		void COpenGLRenderer::PolygonMeshMode(bool bMesh)
		{
			if (bMesh)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//glEnable(GL_CULL_FACE);
			//glCullFace(GL_FRONT);
		}

		void COpenGLRenderer::DestroyTexture(ITexture *texture)
		{
			SAFE_DEL(texture);
		}
	}
}