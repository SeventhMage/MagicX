#ifndef _SE_I_RENDERER_H_
#define _SE_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IRenderQueue.h"
#include "IMaterial.h"

namespace se
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){}
			virtual IRenderDriver *GetRenderDriver() = 0;
			virtual IRenderQueue *CreateRenderQueue(const char *material) = 0;
			virtual void DestroyRenderQueue(IRenderQueue *) = 0;
		};
	}

}

#endif