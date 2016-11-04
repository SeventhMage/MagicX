/************************************************************************/
/* 顶点数组对象                                                         */
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

			//绑定当前顶点数组
			virtual void Bind(){}
			virtual void UnBind(){}

		
			virtual void Render();			
		
		protected:
			IRenderList *m_pRenderList;					//渲染列表
			IShaderProgram *m_pShaderProgram;			//shader程序
		};
	}
}

#endif