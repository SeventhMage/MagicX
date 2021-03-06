/************************************************************************/
/* ��������ļ�                                                         */
/************************************************************************/
#ifndef _MX_INCLUDE_H_
#define _MX_INCLUDE_H_

#include "IMagicX.h"

namespace mx
{
	extern IMagicX *MagicX;

	IMagicX *CreateMagicX(render::ERenderDriverType  renderDriver, int x, int y, int width, int height, bool bFullScreen = false);
	void DestroyMagicX();

#define DEVICEMGR (MagicX->GetDeviceManager())
#define RENDERER (MagicX->GetRenderer())
#define RESOURCEMGR(cast, type) ((cast *)(MagicX->GetResourceManager(type)))
#define SCENEMGR (MagicX->GetSceneManager())
}

#endif