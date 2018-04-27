#ifndef _RENDER_C_GL_DRIVER_WIN_H_
#define _RENDER_C_GL_DRIVER_WIN_H_

#include <windows.h>

namespace mx
{
	class CGLDriverWin
	{
	public:
		CGLDriverWin(HDC hDC);
		~CGLDriverWin(){}
	};
}

#endif