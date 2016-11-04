/************************************************************************/
/* �����������                                                         */
/************************************************************************/

#ifndef _MX_RENDER_C_VERTEX_ARRAY_OBJECT_H_
#define _MX_RENDER_C_VERTEX_ARRAY_OBJECT_H_

#include "render/IVertexArrayObject.h"
#include "render/IRenderable.h"
#include "render/IRenderList.h"

namespace mx
{
	namespace render
	{
		class CVertexArrayObject : public IVertexArrayObject
		{
		public:
			CVertexArrayObject();
			virtual ~CVertexArrayObject();					

			//�󶨵�ǰ��������
			virtual void Bind(){}
			virtual void UnBind(){}

		
			virtual void Render();			
		
		protected:
			IRenderList *m_pRenderList;					//��Ⱦ�б�
			IShaderProgram *m_pShaderProgram;			//shader����
		};
	}
}

#endif