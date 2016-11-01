/************************************************************************/
/* 引擎包含文件                                                         */
/************************************************************************/
#ifndef _MX_INCLUDE_H_
#define _MX_INCLUDE_H_

#include "IMagicX.h"

namespace mx
{
	IMagicX *CreateMagicX(render::ERenderDriverType  renderDriver, int x, int y, int width, int height, bool bFullScreen = false);
	void DestroyMagicX(IMagicX *pMagicX);
}

#endif