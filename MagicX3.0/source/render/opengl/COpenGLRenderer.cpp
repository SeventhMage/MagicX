#include "COpenGLRenderer.h"
#include "COpenGLDriver.h"
#include "GLDebug.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLIndexBufferObject.h"
#include "OpenGLType.h"
#include "COpenGLShaderProgram.h"
#include "COpenGLVertexArrayObject.h"


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
					ibo->Bind();
					GLDebug(glDrawElements(ibo->GetGPUBufferMode(), ibo->GetIndicesNum(), ibo->GetIndexType(), 0));
				}
				else
				{
					COpenGLVertexBufferObject *vbo = dynamic_cast<COpenGLVertexBufferObject *>(pRenderable->GetIndexBufferObject());
					if (vbo)
					{
						vbo->Bind();
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

		IShaderProgram * COpenGLRenderer::CreateShaderProgram()
		{
			return new COpenGLShaderProgram();
		}

		void COpenGLRenderer::DestroyShaderProgram(IShaderProgram *pProgram)
		{
			if (pProgram)
			{
				delete pProgram;
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

	}

}
