#ifndef _MX_RENDER_C_OPENGL_GPU_BUFFER_H_
#define _MX_RENDER_C_OPENGL_GPU_BUFFER_H_

#include <vector>

#include "glew/GL/glew.h"
#include "../../include/IGPUBuffer.h"
#include "../../include/IBufferObject.h"
#include "../../include/IRenderableObject.h"

namespace mx
{
	namespace render
	{
		class COpenGLGPUBuffer : public IGPUBuffer
		{
		public:
			COpenGLGPUBuffer(int stride, bool bNormalize = false);
			virtual ~COpenGLGPUBuffer();

			virtual IRenderableObject *CreateRenderableObject();

			virtual void Begin();
			virtual void CreateVertexBuffer(IRenderableObject *object, void *vertexes, int size, int first, int count, GPUBufferMode mode, GPUBufferUsage usage);
			virtual void AddVertexData(IRenderableObject *object, void *data, int size, int offset);
			virtual void EnableVertexAttrib(VertexAttributeLocation vai, int size, RendererVariableType vertType, int offset);
			virtual void CreateIndexBuffer(IRenderableObject *object, void *indices, int idxCount, RendererVariableType idxType, GPUBufferMode mode, GPUBufferUsage usage);
			virtual void End();

			virtual void Render();

		private:
			std::vector<IRenderableObject *> m_vecRenderableObject;
			GLuint m_hVAO;
			int m_stride;
			bool m_bNormalize;
		};
	}
}

#endif