#include "mx.h"
#include "CMagicX.h"

namespace mx
{

	IMagicX * CreateMagicX(render::ERenderDriverType renderDriver, int x, int y, int width, int height, bool bFullScreen /*= false*/)
	{
#ifdef WIN32
		return new CMagicX(DT_WIN32, renderDriver, x, y, width, height, bFullScreen);
#endif
	}

	void DestroyMagicX(IMagicX *pMagicX)
	{
		if (pMagicX)
		{
			delete pMagicX;
		}
	}

}
