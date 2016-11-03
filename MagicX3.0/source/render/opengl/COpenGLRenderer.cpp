#include "COpenGLRenderer.h"
#include "COpenGLDriver.h"
#include "GLDebug.h"
#include "COpenGLVertexBufferObject.h"
#include "COpenGLIndexBufferObject.h"


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

			}

		}
	}

}
