#ifndef _MX_RENDERER_H_
#define _MX_RENDERER_H_

#include <Windows.h>
#include "IGPUBuffer.h"
#include "IShader.h"
#include "IShaderProgram.h"
#include "ITexture.h"
#include "ITerrainTextureGenerator.h"

namespace mx
{
	namespace render
	{		
		class IRenderer
		{
		public:
			IRenderer(){};
			virtual ~IRenderer(){};

			virtual bool InitRendererWin32(HDC hDC) = 0;
			virtual void SetViewport(int left, int top, int width, int height) = 0;
			virtual IGPUBuffer *CreateGPUBuffer(int stride) = 0;
			virtual void DestroyGPUBuffer(IGPUBuffer *gpuBuffer) = 0;			

			virtual ITexture *CreateTexture(const char *filename, TextureType texType) = 0;
			virtual ITexture *CreateCubeTexture(const char *front, const char *back, const char *left, const char *right, const char *top, const char *bottom)  = 0;			
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