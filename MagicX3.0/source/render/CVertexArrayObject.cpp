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
			m_pMaterial = new CMaterial();
		}

		CVertexArrayObject::~CVertexArrayObject()
		{			
			SAFE_DEL(m_pRenderList);
			SAFE_DEL(m_pMaterial);
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