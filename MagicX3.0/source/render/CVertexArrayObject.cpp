#include "CVertexArrayObject.h"
#include "mx.h"
#include "CRenderList.h"
#include "CMaterial.h"
#include "CRenderable.h"

namespace mx
{
	namespace render
	{		

		CVertexArrayObject::CVertexArrayObject()
		{	
			m_pRenderList = new CRenderList();
		}

		CVertexArrayObject::~CVertexArrayObject()
		{			
			SAFE_DEL(m_pRenderList);
		}
		
		void CVertexArrayObject::Render()
		{			
			Bind();
			if (m_pRenderList)
				m_pRenderList->Render();
			UnBind();
		}		

	}
}