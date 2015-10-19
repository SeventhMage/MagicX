#ifndef _MX_RENDERER_H_
#define _MX_RENDERER_H_

#include <Windows.h>
#include "IGPUBuffer.h"
#include "IShader.h"
#include "IShaderProgram.h"

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

			virtual void Render() = 0;
		};		
	}
}

#endif