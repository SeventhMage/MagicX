#ifndef _RENDER_I_TEXTURE_H_
#define _RENDER_I_TEXTURE_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		class ITexture
		{
		public:
			virtual ~ITexture(){}
			virtual ubyte *GetData() = 0;
		};
	}
}

#endif