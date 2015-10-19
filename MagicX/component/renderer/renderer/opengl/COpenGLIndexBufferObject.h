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
			COpenGLIndexBufferObject(void *indices, int idxCount, RendererVariableType idxType, GPUBufferMode mode, GPUBufferUsage usage);
			virtual ~COpenGLIndexBufferObject();

			virtual void BufferData(void *indices, int idxSize);
			virtual void BufferSubData(void *data, int size, int offset) {}
			virtual GPUBufferType GetBufferType(){ return GBT_VERTEX; };
			virtual GPUBufferMode GetGPUBufferMode() { return m_gpuBufferMode; }
			virtual GPUBufferUsage GetGPUBufferUsage() { return m_gpuBufferUsage; }
			virtual int GetVertexNum() { return 0; }
			virtual uint GetHandle() { return m_IBO; }

			
			virtual uint GetHandle() const { return m_IBO; }

			RendererVariableType GetIndexType() { return RVT_FLOAT; }
			Byte *GetIndexBufferData() { return NULL; }

			int GetGLGPUBufferMode() { return 0; };
			int GetGLGPUBufferUsage() { return 0; };
		private:
			uint m_IBO;
			GPUBufferMode m_gpuBufferMode;
			GPUBufferUsage m_gpuBufferUsage;
		};
	}
}

#endif