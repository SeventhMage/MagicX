#ifndef _MX_RENDER_I_GPU_BUFFER_H_
#define _MX_RENDER_I_GPU_BUFFER_H_

#include "common/mxDef.h"
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
			virtual ~IGPUBuffer(){};

			virtual void Begin() = 0;
			virtual IRenderableObject *CreateRenderableObject() = 0;
			virtual void CreateVertexBuffer(IRenderableObject *object, void *vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual void AddVertexData(IRenderableObject *object, void *data, int size, int offset) = 0;
			virtual void EnableVertexAttrib(VertexAttributeLocation vai, int size, RendererVariableType vertType, int offset) = 0;
			virtual void CreateIndexBuffer(IRenderableObject *object, void *indices, int idxCount, RendererVariableType idxType, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual void End() = 0;

			virtual void Render() = 0;
		};
	}
}

#endif