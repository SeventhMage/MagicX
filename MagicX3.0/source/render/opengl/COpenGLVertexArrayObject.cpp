#include "COpenGLVertexArrayObject.h"
#include "GLDebug.h"
#include "OpenGLType.h"
#include "COpenGLShaderProgram.h"

namespace mx
{
	namespace render
	{


		COpenGLVertexArrayObject::COpenGLVertexArrayObject()
		{
			GLDebug(glGenVertexArrays(1, &m_hVAO));			
		}

		COpenGLVertexArrayObject::~COpenGLVertexArrayObject()
		{
			GLDebug(glDeleteVertexArrays(1, &m_hVAO));
		}

		void COpenGLVertexArrayObject::BeginRender()
		{			
			Bind();			
		}


		void COpenGLVertexArrayObject::EndRender()
		{
			UnBind();
			if (m_pRenderList)
				m_pRenderList->Clear();
		}

		void COpenGLVertexArrayObject::Bind()
		{
			GLDebug(glBindVertexArray(m_hVAO));
		}

		void COpenGLVertexArrayObject::UnBind()
		{
			GLDebug(glBindVertexArray(0));
		}

		void COpenGLVertexArrayObject::EnableVertexAttrib(VertexAttributeLocation val, int size, RendererVariableType vertType, int stride, int offset)
		{
			GLDebug(glEnableVertexAttribArray(val));
			GLDebug(glVertexAttribPointer(val, size, GetGLVariableType(vertType), false, stride, (GLvoid *)offset));
		}

	}
}