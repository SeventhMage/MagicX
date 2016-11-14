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

			m_pShaderProgram = new COpenGLShaderProgram();
		}

		COpenGLVertexArrayObject::~COpenGLVertexArrayObject()
		{
			GLDebug(glDeleteVertexArrays(1, &m_hVAO));
			if (m_pShaderProgram)
				delete m_pShaderProgram;
		}

		void COpenGLVertexArrayObject::BeginRender()
		{			
			if (m_pShaderProgram)
			{
				GLDebug(glUseProgram(m_pShaderProgram->GetHandle()));
				m_pShaderProgram->Bind();
			}

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