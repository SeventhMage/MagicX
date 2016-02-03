#ifndef _MX_RENDER_C_OPENGL_GPU_BUFFER_H_
#define _MX_RENDER_C_OPENGL_GPU_BUFFER_H_

#include <vector>

#include "glew/GL/glew.h"
#include "render/IGPUBuffer.h"
#include "render/IBufferObject.h"
#include "render/IRenderableObject.h"

namespace mx
{
	namespace render
	{
		class COpenGLGPUBuffer : public IGPUBuffer
		{
		public:
			COpenGLGPUBuffer(bool bNormalize = false);
			virtual ~COpenGLGPUBuffer();

			virtual IRenderableObject *CreateRenderableObject();

			virtual void Begin();						
			virtual void EnableVertexAttrib(VertexAttributeLocation vai, int size, RendererVariableType vertType, int stride, int offset);			
			virtual void End();

			virtual void Render();

		private:
			std::vector<IRenderableObject *> m_vecRenderableObject;
			GLuint m_hVAO;
			bool m_bNormalize;
		};
	}
}

#endif