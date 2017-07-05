#ifndef _RENDER_C_SOFT_TEXTURE_H_
#define _RENDER_C_SOFT_TEXTURE_H_

#include "render/ITexture.h"

namespace se
{
	namespace render
	{
		class CSoftTexture : public ITexture
		{
		public:
			CSoftTexture(int id);
			virtual ~CSoftTexture();

			virtual ubyte *GetData(){ return nullptr; }
		};
	}
}

#endif