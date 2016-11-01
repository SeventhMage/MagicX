/************************************************************************/
/* 渲染驱动，不同的驱动使用不能渲染引擎，如OpenGL、DX、软引擎等         */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDER_DRIVER_H_
#define _MX_RENDER_I_RENDER_DRIVER_H_

#ifdef WIN32
#include <windows.h>
#endif

namespace mx
{
	namespace render
	{
		//渲染驱动类型
		enum ERenderDriverType
		{
			RDT_OPENGL,				//使用OpenGL接口
			RDT_DIRECTX,			//使用DirectX接口
			RDT_SOFTWARE,			//使用软件引擎
		};
		class IRenderDriver
		{
		public:
			virtual ~IRenderDriver(){};
			
#ifdef WIN32
			virtual void InitDriverWin32(HDC hDc) = 0;
#endif
			virtual void Render() = 0;
			virtual void OnSize(int x, int y, int width, int height) = 0;
		};
	}
}

#endif