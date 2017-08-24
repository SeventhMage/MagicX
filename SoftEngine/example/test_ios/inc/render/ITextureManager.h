#ifndef _RENDER_I_TEXTURE_MANAGER_H_
#define _RENDER_I_TEXTURE_MANAGER_H_

#include "ITexture.h"

namespace se
{
	namespace render
	{
		class ITextureManager
		{
		public:
			virtual ~ITextureManager(){}

			virtual int CreateTexture(const char *filename) = 0;
			virtual void DestroyTexture(int textureId) = 0;
			virtual ITexture *GetTexture(int textureId) = 0;
		};
	}
}

#endif