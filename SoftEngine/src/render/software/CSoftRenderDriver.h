#ifndef _SE_C_SOFT_RENDER_DRIVER_H_
#define _SE_C_SOFT_RENDER_DRIVER_H_

#include "render/IRenderDriver.h"

namespace se
{
	namespace render
	{
		class CSoftRenderDriver : public IRenderDriver
		{
		public:		
#ifdef WIN32
			virtual void InitDriverWin32(HDC hDc) {}
#endif
			virtual void OnSize(int x, int y, int width, int height) {}
		};
	}
}

#endif