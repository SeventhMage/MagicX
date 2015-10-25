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

			virtual ITexture *CreateTexture(const char *filename, TextureType texType);
			virtual ITexture *CreateCubeTexture(const char *front, const char *back, const char *left, const char *right, const char *top, const char *bottom);

			virtual void ClearColor(float r, float g, float b, float a);
			virtual void Clear(uint bit);
			virtual void Enable(uint bit);
			virtual void Disable(uint bit);

		private:
			std::vector<IGPUBuffer *> m_vecBuffer;
		};
	}
}

#endif