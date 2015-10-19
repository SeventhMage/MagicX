#ifndef _MX_RENDER_C_OPENGL_RENDERER_H_
#define _MX_RENDER_C_OPENGL_RENDERER_H_

#include "../../include/IRenderer.h"
#include <vector>

namespace mx
{
	namespace render
	{
		class COpenGLRenderer : public IRenderer
		{
		public:
			COpenGLRenderer();
			virtual ~COpenGLRenderer();

			virtual bool InitRendererWin32(HDC hDC);
			virtual void SetViewport(int left, int top, int width, int height);
			virtual void Render();

			virtual IGPUBuffer *CreateGPUBuffer(int stride);
			virtual void DestroyGPUBuffer(IGPUBuffer *gpuBuffer);

		private:
			std::vector<IGPUBuffer *> m_vecBuffer;
		};
	}
}

#endif