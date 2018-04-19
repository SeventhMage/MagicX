#ifndef _RENDER_C_GL_DRIVER_WIN_H_
#define _RENDER_C_GL_DRIVER_WIN_H_

#include "CGLDriver.h"

namespace mx
{
	class CGLDriverWin
	{
	public:
		CGLDriverWin(int handle);
		~CGLDriverWin(){}
	};
}

#endif