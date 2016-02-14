#ifndef _MX_RENDER_I_GPU_BUFFER_H_
#define _MX_RENDER_I_GPU_BUFFER_H_

#include <vector>

#include "mxType.h"
#include "IShaderProgram.h"
#include "ERender.h"
#include "IRenderableObject.h"
#include "SVertexAttribute.h"

namespace mx
{
	namespace render
	{
		class IGPUBuffer
		{
		public:
			typedef std::vector<IRenderableObject *> RenderableTable;
			virtual ~IGPUBuffer(){};

			virtual void Begin() = 0;
			virtual IRenderableObject *CreateRenderableObject() = 0;	
			virtual RenderableTable &GetRenderableObject() = 0;
			virtual void EnableVertexAttrib(VertexAttributeLocation vai, int size, RendererVariableType vertType, int stride, int offset) = 0;			
			virtual void End() = 0;

			virtual void Render() = 0;
		};
	}
}

#endif