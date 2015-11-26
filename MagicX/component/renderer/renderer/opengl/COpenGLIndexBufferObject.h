#ifndef _MX_RENDER_COPENGL_INDEX_BUFFER_H_
#define _MX_RENDER_COPENGL_INDEX_BUFFER_H_

#include "glew/GL/glew.h"
#include "../../include/ERender.h"
#include "../../include/IBufferObject.h"


namespace mx
{
	namespace render
	{
		class COpenGLIndexBufferObject : public IBufferObject
		{
		public:
			COpenGLIndexBufferObject(void *indices, uint idsCount, RendererVariableType idxType, uint vertCount, GPUBufferMode mode, GPUBufferUsage usage);
			virtual ~COpenGLIndexBufferObject();

			virtual void BufferData(void *indices, int idxSize);
			virtual void BufferSubData(void *data, int size, int offset) {}
			virtual GPUBufferType GetBufferType(){ return GBT_VERTEX; };
			virtual GPUBufferMode GetGPUBufferMode() { return m_gpuBufferMode; }
			virtual GPUBufferUsage GetGPUBufferUsage() { return m_gpuBufferUsage; }
			virtual int GetVerticesNum() { return m_uVerticesNum; }
			virtual uint GetHandle() { return m_IBO; }

			
			virtual uint GetHandle() const { return m_IBO; }

			RendererVariableType GetIndexType() { return RVT_UINT; }
		private:
			uint m_IBO;
			GPUBufferMode m_gpuBufferMode;
			GPUBufferUsage m_gpuBufferUsage;
			uint m_uVerticesNum;
		};
	}
}

#endif