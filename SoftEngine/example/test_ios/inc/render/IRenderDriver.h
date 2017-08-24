/************************************************************************/
/* 与设备相关接口，连接渲染器与设备                                     */
/************************************************************************/

#ifndef _SE_I_RENDER_DRIVER_H_
#define _SE_I_RENDER_DRIVER_H_

#include "SRenderContext.h"

namespace se
{
	namespace render
	{
		enum RenderDriverType
		{
			RDT_SOFTWARE,
		};

		class IRenderDriver
		{
		public:
			virtual ~IRenderDriver(){}
			
			virtual void InitDriver(const SRenderContext &context) = 0;
			virtual void OnSize(int x, int y, int width, int height) {}
			virtual RenderDriverType GetDriverType() = 0;			
		};
	}
}

#endif