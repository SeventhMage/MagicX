#ifndef _I_TEXTURE_H_INC
#define _I_TEXTURE_H_INC

#include "ERender.h"

namespace mx
{
	namespace render
	{
		class ITexture
		{
		public:
			ITexture() {};
			virtual ~ITexture(){};

			virtual bool Create(const char *filename, TextureType texType) = 0;
			virtual TextureType GetTextureType() { return TT_2D; };
		};
	}
}

#endif // !_I_TEXTURE_H_INC
