/************************************************************************/
/* ��������                                                             */
/************************************************************************/

#ifndef _MX_RENDER_I_VERTEX_ARRAY_OBJECT_H_
#define _MX_RENDER_I_VERTEX_ARRAY_OBJECT_H_

#include "SVertexAttribute.h"
#include "ERender.h"
#include "IRenderable.h"
#include "IShaderProgram.h"
#include "IRenderList.h"

namespace mx
{
	namespace render
	{
		class IVertexArrayObject
		{
		public:
			virtual ~IVertexArrayObject(){}

			//������������
			virtual void EnableVertexAttrib(VertexAttributeLocation vai, int size,
				RendererVariableType vertType, int stride, int offset) = 0;

			virtual IShaderProgram *GetShaderProgram() = 0;
			virtual IRenderList *GetRenderList() = 0;

			virtual void Bind() = 0;
			virtual void UnBind() = 0;

			//��Ⱦ
			virtual void Render() = 0;
		};
	}
}

#endif