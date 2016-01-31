#ifndef _MX_I_RENDERABLE_OBJECT_H_
#define _MX_I_RENDERABLE_OBJECT_H_

#include "IShaderProgram.h"
#include "IBufferObject.h"
#include "ITexture.h"

namespace mx
{
	namespace render
	{
		class IRenderableObject
		{
		public:
			virtual ~IRenderableObject() {};

			virtual void CreateVertexBufferObject(void *vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual void CreateIndexBufferObject(void *indices, uint idsCount, RendererVariableType idsType, uint vertCount, GPUBufferMode mode, GPUBufferUsage usage) = 0;
			virtual IBufferObject *GetVertexBufferObject() = 0;
			virtual IBufferObject *GetIndexBufferObject() = 0;
			virtual IShaderProgram *GetShaderProgram() = 0;
			virtual void EnableIndexBuffer(bool enable) = 0;
			virtual bool IsEnabledIndexBuffer() = 0;
			virtual void BindTexture(int unit = 0) = 0;
			virtual void SetTexture(ITexture *texture, int unit = 0) = 0;
		};
	}
}

#endif
