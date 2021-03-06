/************************************************************************/
/* OpenGL顶点数组对象                                                   */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_VERTEX_ARRAY_OBJECT_H_
#define _MX_RENDER_C_OPENGL_VERTEX_ARRAY_OBJECT_H_

#include "../CVertexArrayObject.h"
#include "GL/glew.h"

namespace mx
{
	namespace render
	{
		class COpenGLVertexArrayObject : public CVertexArrayObject
		{
		public:
			COpenGLVertexArrayObject();
			virtual ~COpenGLVertexArrayObject();			

			virtual void Bind();			
			virtual void UnBind();
			virtual void EnableVertexAttrib(VertexAttributeLocation vai, int size,
				RendererVariableType vertType, int stride, int offset);
		private:
			GLuint m_hVAO;			
		};
	}
}

#endif