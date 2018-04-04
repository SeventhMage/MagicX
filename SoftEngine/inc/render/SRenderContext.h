/*
**初始化渲染驱动参数
*/
#ifndef _RENDER_S_RENDER_CONTEXT_H_
#define _RENDER_S_RENDER_CONTEXT_H_

#ifdef WIN32
#include <windows.h>
#endif

namespace se
{
	namespace render
	{
		struct SRenderContext
		{
			int iWidth;
			int iHeight;
#ifdef WIN32
			HDC hDC;
#endif

#ifdef __APPLE__

#endif
		};

	}
}

#endif