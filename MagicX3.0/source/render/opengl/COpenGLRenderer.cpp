#include "COpenGLRenderer.h"
#include "COpenGLDriver.h"
#include "GLDebug.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLIndexBufferObject.h"
#include "OpenGLType.h"
#include "COpenGLShaderProgram.h"
#include "COpenGLVertexArrayObject.h"
#include "COpenGLTexture.h"
#include "resource/IImageManager.h"
#include "resource/IImage.h"
#include "mx.h"



namespace mx
{
	namespace render
	{


		COpenGLRenderer::COpenGLRenderer()
			:CRenderer(new COpenGLDriver())
		{
			
		}

		COpenGLRenderer::~COpenGLRenderer()
		{
			
		}

		void COpenGLRenderer::Render(IRenderable *pRenderable)
		{
			if (pRenderable)
			{
				pRenderable->Bind();
				COpenGLIndexBufferObject *ibo = dynamic_cast<COpenGLIndexBufferObject *>(pRenderable->GetIndexBufferObject());
				if (ibo)
				{
					GLDebug(glDrawElements(ibo->GetGPUBufferMode(), ibo->GetIndicesNum(), ibo->GetIndexType(), 0));
				}
				else
				{
					COpenGLVertexBufferObject *vbo = dynamic_cast<COpenGLVertexBufferObject *>(pRenderable->GetVertexBufferObject());
					if (vbo)
					{
						GLDebug(glDrawArrays(vbo->GetGPUBufferMode(), vbo->GetGLGPUBufferFirst(), vbo->GetVertexNum()));
					}
				}
				pRenderable->UnBind();
			}

		}

		IBufferObject * COpenGLRenderer::CreateVertexBufferObject(void *vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage)
		{
			return new COpenGLVertexBufferObject(vertexes, size, first, count, GetGLGPUBufferMode(mode), GetGLGPUBufferUsage(usage));
		}

		IBufferObject * COpenGLRenderer::CreateIndexBufferObject(void *indices, uint idsCount, RendererVariableType idsType, GPUBufferMode mode, GPUBufferUsage usage)
		{
			return new COpenGLIndexBufferObject(indices, idsCount, GetGLVariableType(idsType), GetGLGPUBufferMode(mode), GetGLGPUBufferUsage(usage));
		}

		void COpenGLRenderer::DestroyBufferObject(IBufferObject *object)
		{
			if (object)
			{
				delete object;
			}
		}


		IVertexArrayObject * COpenGLRenderer::CreateVertexArrayObject()
		{
			return new COpenGLVertexArrayObject();
		}

		void COpenGLRenderer::DestroyVertexArrayObject(IVertexArrayObject *pObject)
		{
			if (pObject)
				delete pObject;
		}

		ITexture * COpenGLRenderer::CreateTexture(const char *filename)
		{
			resource::IImageManager *pIMageMgr = (IImageManager *)RESOURCEMGR(RT_IMAGE);
			if (pIMageMgr)
			{
				resource::IImage *pImage = (resource::IImage *)pIMageMgr->LoadResource(filename);
				if (pImage)
				{
					ITexture *pTexture = new COpenGLTexture();
					pTexture->Create2D(GetGLColorFormat((pImage->GetComponents())), 
						pImage->GetWidth(), pImage->GetHeight(), GetGLColorFormat((pImage->GetFormat())), GL_UNSIGNED_BYTE, pImage->GetData());
					pIMageMgr->UnLoadResource(pImage);
					return pTexture;
				}
			}
			return nullptr;
		}

		void COpenGLRenderer::DestroyTexture(ITexture *pTexture)
		{
			if (pTexture)
				delete pTexture;
		}
	}

}
