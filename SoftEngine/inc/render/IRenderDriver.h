/************************************************************************/
/* 与设备相关接口，连接渲染器与设备                                     */
/************************************************************************/

#ifndef _SE_I_RENDER_DRIVER_H_
#define _SE_I_RENDER_DRIVER_H_

#ifdef WIN32
#include <windows.h>
#endif

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
#ifdef WIN32
			virtual void InitDriverWin32(HDC hDc) {}
#endif
			virtual void OnSize(int x, int y, int width, int height) {}
		};
	}
}

#endif