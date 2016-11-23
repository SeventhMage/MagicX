/************************************************************************/
/* �����������                                                         */
/************************************************************************/

#ifndef _MX_RENDER_C_VERTEX_ARRAY_OBJECT_H_
#define _MX_RENDER_C_VERTEX_ARRAY_OBJECT_H_

#include "render/IVertexArrayObject.h"
#include "render/IMaterial.h"

namespace mx
{
	namespace render
	{
		class CVertexArrayObject : public IVertexArrayObject
		{
		public:
			CVertexArrayObject();
			virtual ~CVertexArrayObject();								


			virtual IRenderList *GetRenderList() { return m_pRenderList; }
			
			virtual void Render();			
		
		protected:
			IRenderList *m_pRenderList;					//��Ⱦ�б�	
			IMaterial *m_pMaterial;						//����
		};
	}
}

#endif