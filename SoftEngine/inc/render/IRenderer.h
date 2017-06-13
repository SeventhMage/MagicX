#ifndef _SE_I_RENDERER_H_
#define _SE_I_RENDERER_H_

#include "IRenderDriver.h"

namespace se
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){}
			virtual IRenderDriver *GetRenderDriver() = 0;
			virtual 
		};
	}

}

#endif