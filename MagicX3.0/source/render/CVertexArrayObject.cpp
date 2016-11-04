#include "CVertexArrayObject.h"
#include "mx.h"
#include "CRenderList.h"

namespace mx
{
	namespace render
	{		

		CVertexArrayObject::CVertexArrayObject()
		{
			m_pShaderProgram = RENDERER->CreateShaderProgram();
			m_pRenderList = new CRenderList();
		}

		CVertexArrayObject::~CVertexArrayObject()
		{
			RENDERER->DestroyShaderProgram(m_pShaderProgram);
			if (m_pRenderList)
				delete m_pRenderList;
		}

		
		void CVertexArrayObject::Render()
		{
			Bind();
			if (m_pShaderProgram)
				m_pShaderProgram->Bind();
			if (m_pRenderList)
				m_pRenderList->Render();
			UnBind();
		}		

	}
}