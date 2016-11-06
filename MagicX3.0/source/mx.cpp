#include "mx.h"
#include "CMagicX.h"

namespace mx
{
	IMagicX *MagicX = NULL;

	IMagicX * CreateMagicX(render::ERenderDriverType renderDriver, int x, int y, int width, int height, bool bFullScreen /*= false*/)
	{
#ifdef WIN32
		MagicX = new CMagicX(DT_WIN32, renderDriver, x, y, width, height, bFullScreen);
		return MagicX;
#endif
	}

	void DestroyMagicX()
	{
		if (MagicX)
		{
			delete MagicX;
		}
	}

}
