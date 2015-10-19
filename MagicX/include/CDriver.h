#ifndef _MX_C_DRIVER_H_INC_
#define _MX_C_DRIVER_H_INC_

#include "common/mxDef.h"
#include "common/CSingleton.h"
#include "IDevice.h"
#include "IRenderer.h"

namespace mx
{
	using namespace device;
	using namespace render;

	class CDriver : public CSingleton<CDriver>
	{
	public:
		CDriver();
		~CDriver();

		IDevice *CreateDevice(uint uWidth, uint uHeight, bool bFullScreen = false, RendererType renderType = RT_OPENGL);
		void Run();
	};	
}

#endif