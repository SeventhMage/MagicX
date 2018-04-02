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
			virtual int GetID() const = 0;
			virtual ubyte *GetData()const = 0;
			virtual ulong GetSize()const = 0;
			virtual int GetWidth()const = 0;
			virtual int GetHeight()const = 0;
		};
	}
}

#endif