/************************************************************************/
/* 连接设置与渲染器的驱动,初始化渲染器                                  */
/************************************************************************/
#ifndef _MX_RENDER_IRENDERDRIVER_H_
#define _MX_RENDER_IRENDERDRIVER_H_

#include "device/IDeviceDriver.h"
#include "mxType.h"
#include "IRenderer.h"

namespace mx
{
	namespace render
	{
		class IRenderDriver : public device::IDeviceDriver
		{
		public:
			IRenderDriver(){}
			virtual ~IRenderDriver(){}
			virtual device::EDeviceDriverType GetDriverType(){ return device::E_DDT_RENDERER; }
			virtual void OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight) = 0;
			virtual IRenderer *GetRenderer() = 0;
		};
	}
}

#endif