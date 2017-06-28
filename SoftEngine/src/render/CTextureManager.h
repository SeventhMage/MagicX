#ifndef _RENDER_C_TEXTURE_MANAGER_H_
#define _RENDER_C_TEXTURE_MANAGER_H_

#include "render/ITextureManager.h"
#include "base/CSingleton.h"

#include <map>

namespace se
{
	namespace render
	{
		class CTextureManager : public ITextureManager, public base::CSingleton<CTextureManager>
		{
		public:
			CTextureManager();
			virtual ~CTextureManager();

			virtual int CreateTexture(const char *filename);
			virtual void DestroyTexture(int textureId);
			virtual ITexture *GetTexture(int textureId);

		private:
			std::map<int, ITexture *>m_mapTexture;
		};
	}
}

#endif