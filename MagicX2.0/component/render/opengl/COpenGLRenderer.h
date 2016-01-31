#ifndef _MX_RENDER_OPENGLRENDERER_H_
#define _MX_RENDER_OPENGLRENDERER_H_

#include <vector>

#include "render/IRenderer.h"
#include "render/IGPUBuffer.h"
#include "render/ITerrainTextureGenerator.h"

namespace mx
{
	namespace render
	{
		class COpenGLRenderer : public IRenderer
		{
		public:
			COpenGLRenderer();
			virtual ~COpenGLRenderer();
			virtual void DrawLine(const core::CVector3 &vFrom, const core::CVector3 &vTo, const SColor &color = SColor(1, 0, 0, 0));
			virtual void DrawImage(const resource::IImage *image, uint uScreenX = 0, uint uScreenY = 0);
			virtual void DrawMesh(const resource::IMesh *pMesh);

			virtual void AddMesh(resource::IMesh *pMesh);
			virtual void DrawRenderList();

			virtual void Render();

			virtual IGPUBuffer *CreateGPUBuffer(int stride);
			virtual void DestroyGPUBuffer(IGPUBuffer *gpuBuffer);

			virtual ITexture *CreateTexture(const char *filename, TextureType texType);
			virtual ITexture *CreateCubeTexture(const char *front, const char *back, const char *left, const char *right, const char *top, const char *bottom);
			virtual void DestroyTexture(ITexture *texture);

			virtual void ClearColor(float r, float g, float b, float a);
			virtual void Clear(uint bit);
			virtual void Enable(uint bit);
			virtual void Disable(uint bit);
			virtual void PolygonMeshMode(bool bMesh);

			virtual ITerrainTextureGenerator *GetTextureGenerator() { return m_pTerrainTextureGenerator; }
		private:
			std::vector<IGPUBuffer *> m_vecBuffer;
			ITerrainTextureGenerator *m_pTerrainTextureGenerator;
		};
	}
}

#endif