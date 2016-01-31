#ifndef _MX_RENDER_IRENDERER_H_
#define _MX_RENDER_IRENDERER_H_

#include "core/CVector3.h"
#include "resource/IMesh.h"
#include "resource/IImage.h"
#include "SColor.h"
#include "ITerrainTextureGenerator.h"
#include "IGPUBuffer.h"

namespace mx
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){};
			virtual void DrawLine(const core::CVector3 &vFrom, const core::CVector3 &vTo, const SColor &color = SColor(1, 0, 0, 0)) = 0;
			virtual void DrawImage(const resource::IImage *image, uint uScreenX = 0, uint uScreenY = 0) = 0;
			virtual void DrawMesh(const resource::IMesh *pMesh) = 0;
			
			virtual void AddMesh(resource::IMesh *pMesh) = 0;
			virtual void DrawRenderList() = 0;


			virtual IGPUBuffer *CreateGPUBuffer(int stride) = 0;
			virtual void DestroyGPUBuffer(IGPUBuffer *gpuBuffer) = 0;

			virtual ITexture *CreateTexture(const char *filename, TextureType texType) = 0;
			virtual ITexture *CreateCubeTexture(const char *front, const char *back, const char *left, const char *right, const char *top, const char *bottom) = 0;
			virtual void DestroyTexture(ITexture *texture) = 0;

			virtual void ClearColor(float r, float g, float b, float a) = 0;
			virtual void Clear(uint) = 0;
			virtual void Enable(uint) = 0;
			virtual void Disable(uint) = 0;
			virtual void PolygonMeshMode(bool bMesh) = 0;

			virtual ITerrainTextureGenerator *GetTextureGenerator() = 0;

			virtual void Render() = 0;
		};
	}
}

#endif