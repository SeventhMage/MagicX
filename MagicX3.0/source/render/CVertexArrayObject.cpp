#include "CVertexArrayObject.h"
#include "mx.h"
#include "CRenderList.h"

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
			if (m_pRenderList)
				delete m_pRenderList;
		}

		
		void CVertexArrayObject::Render()
		{
			BeginRender();
			if (m_pRenderList)
				m_pRenderList->Render();
			EndRender();
		}		

	}
}