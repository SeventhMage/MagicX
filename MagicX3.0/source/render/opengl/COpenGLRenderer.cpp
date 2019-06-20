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
#include "COpenGLRenderTargetManager.h"
#include "mx.h"



namespace mx
{
	namespace render
	{


		COpenGLRenderer::COpenGLRenderer()
			:CRenderer(new COpenGLDriver())
			, m_pShadowMap(nullptr)
			, m_triangleNum(0)
		{
			//m_pShadowMap = new COpenGLShadowMap();
			m_pRenderTargetMgr = new COpenGLRenderTargetManager();
		}

		COpenGLRenderer::~COpenGLRenderer()
		{
			SAFE_DEL(m_pShadowMap);
			SAFE_DEL(m_pRenderTargetMgr);
		}

		void COpenGLRenderer::Render(IRenderable *pRenderable)
		{
			if (pRenderable)
			{
				for (uint j = 0; j < RA_NUM; ++j)
				{
					GLenum attr = GetGLRenderAttr((RenderAttribute)j);
					if (pRenderable->IsEnabled((RenderAttribute)j))
						glEnable(attr);
					else
						glDisable(attr);
				}

				pRenderable->Bind();

				COpenGLIndexBufferObject *ibo = dynamic_cast<COpenGLIndexBufferObject *>(pRenderable->GetIndexBufferObject());
				if (ibo)
				{
					GLDebug(glDrawElements(ibo->GetGPUBufferMode(), ibo->GetIndicesNum(), ibo->GetIndexType(), 0));
					m_triangleNum += ibo->GetIndicesNum()/ 3;
				}
				else
				{
					COpenGLVertexBufferObject *vbo = dynamic_cast<COpenGLVertexBufferObject *>(pRenderable->GetVertexBufferObject());
					if (vbo)
					{
						GLDebug(glDrawArrays(vbo->GetGPUBufferMode(), vbo->GetGLGPUBufferFirst(), vbo->GetVertexNum()));
						m_triangleNum += vbo->GetVertexNum()/ 3;
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
			IVertexArrayObject *pVAO = new COpenGLVertexArrayObject();
			AddVertexArrayObject(pVAO);
			return pVAO;
		}

		void COpenGLRenderer::DestroyVertexArrayObject(IVertexArrayObject *pObject)
		{
			if (pObject)
			{
				RemoveVertexArrayObject(pObject);
				delete pObject;
			}			
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
						pImage->GetWidth(), pImage->GetHeight(), GetGLColorFormat((pImage->GetFormat())), GetGLPixelType(pImage->GetPixelType()), pImage->GetData());
					pIMageMgr->UnLoadResource(pImage);
					return pTexture;
				}
			}
			return nullptr;
		}

		ITexture * COpenGLRenderer::CreateCubeTexture(const char *right, const char *left, const char *top, const char *bottom, const char *front, const char *back)
		{
			resource::IImageManager *pIMageMgr = (IImageManager *)RESOURCEMGR(RT_IMAGE);
			if (pIMageMgr)
			{
				const char *file[6] = { right, left, top, bottom, front, back };
				resource::IImage *pImage[6] = { 0 };

				bool bLoadSucess = true;
				for (int i = 0; i < 6; ++i)
				{
					pImage[i] = (resource::IImage *)pIMageMgr->LoadResource(file[i]);
					if (!pImage[i])
					{
						bLoadSucess = false;
						break;
					}
				}

				ITexture *pTexture = nullptr;
				if (bLoadSucess)
				{
					pTexture = new COpenGLTexture();
					pTexture->CreateCube(pImage[0], pImage[1], pImage[2], pImage[3], pImage[4], pImage[5]);
				}				

				for (int i = 0; i < 6; ++i)
				{
					pIMageMgr->UnLoadResource(pImage[i]);
				}
				return pTexture;
				
			}
			return nullptr;
		}

		void COpenGLRenderer::DestroyTexture(ITexture *pTexture)
		{
			if (pTexture)
				delete pTexture;
		}

		void COpenGLRenderer::BeginRender()
		{
			m_triangleNum = 0;
		}

		IShaderProgram * COpenGLRenderer::CreateShaderProgram()
		{
			return new COpenGLShaderProgram();
		}

		void COpenGLRenderer::DestroyShaderProgram(IShaderProgram *pShaderProgram)
		{
			if (pShaderProgram)
				delete pShaderProgram;
		}


	}

}
