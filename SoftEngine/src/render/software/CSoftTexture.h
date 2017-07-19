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
			CSoftTexture(int id, ubyte *pData, ulong size, int width, int height);
			virtual ~CSoftTexture();

			virtual ubyte *GetData()const{ return m_pData; }
			virtual ulong GetSize()const{ return m_size; }
			virtual int GetWidth()const { return m_width; }
			virtual int GetHeight()const { return m_height; }
		private:
			int m_id;
			ubyte *m_pData;
			ulong m_size;;
			int m_width;
			int m_height;
		};
	}
}

#endif