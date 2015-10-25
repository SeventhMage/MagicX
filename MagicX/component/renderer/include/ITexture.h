#ifndef _I_TEXTURE_H_INC
#define _I_TEXTURE_H_INC

#include "ERender.h"
#include "common/mxDef.h"

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
			virtual bool CreateCube(const char *front, const char *back, const char *left, const char *right, const char *top, const char *bottom) = 0;
			virtual TextureType GetTextureType() = 0;
			virtual uint GetHandle() = 0;
		};
	}
}

#endif // !_I_TEXTURE_H_INC
