/************************************************************************/
/* 渲染器接口                                                           */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERER_H_
#define _MX_RENDER_I_RENDERER_H_

#include "IRenderDriver.h"
#include "IBufferData.h"
#include "IRenderable.h"

namespace mx
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){};

			//获取渲染器驱动程序
			virtual IRenderDriver *GetRenderDriver() = 0;

			//渲染
			virtual void Render() = 0;
		};
	}
}

#endif