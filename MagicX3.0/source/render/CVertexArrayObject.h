/************************************************************************/
/* �����������                                                         */
/************************************************************************/

#ifndef _MX_RENDER_C_VERTEX_ARRAY_OBJECT_H_
#define _MX_RENDER_C_VERTEX_ARRAY_OBJECT_H_

#include "render/IVertexArrayObject.h"

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

			//�󶨵�ǰ��������
			virtual void BeginRender() {}
			virtual void Render();			
			virtual void EndRender(){}
		
		protected:
			IRenderList *m_pRenderList;					//��Ⱦ�б�			
		};
	}
}

#endif