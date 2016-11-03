#include "COpenGLRenderer.h"
#include "COpenGLDriver.h"
#include "GLDebug.h"
#include "../CRenderList.h"
#include "../../MagicX2.0/component/render/opengl/COpenGLIndexBufferObject.h"
#include "../../MagicX2.0/component/render/opengl/OpenGLType.h"
#include "COpenGLVertexBufferObject.h"


namespace mx
{
	namespace render
	{


		COpenGLRenderer::COpenGLRenderer()
		{
			m_pRenderDriver = new COpenGLDriver();
			m_pRenderQueue = new CRenderList();
		}

		COpenGLRenderer::~COpenGLRenderer()
		{
			delete m_pRenderDriver;
			delete m_pRenderQueue;
		}

		void COpenGLRenderer::Render()
		{
			if (m_pRenderQueue)
			{
				RENDER_LIST rend_list = m_pRenderQueue->GetRenderList();
				for (auto it = rend_list.begin(); it != rend_list.end(); ++it)
				{
					(*it)->Bind();
					COpenGLIndexBufferObject *ibo = dynamic_cast<COpenGLIndexBufferObject *>((*it)->GetIndexBufferObject());
					if (ibo)
					{
						ibo->Bind();
						GLDebug(glDrawElements(ibo->GetGPUBufferMode(), ibo->GetIndicesNum(), ibo->GetIndexType(), 0));
					}
					else
					{
						COpenGLVertexBufferObject *vbo = dynamic_cast<COpenGLVertexBufferObject *>((*it)->GetIndexBufferObject());
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
}