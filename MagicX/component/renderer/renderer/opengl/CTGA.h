#ifndef _MX_IO_CTGA_H_
#define _MX_IO_CTGA_H_

#include "glew/GL/glew.h"
#include "common/mxDef.h"

namespace mx
{
	namespace render
	{
		// Define targa header. This is only used locally.
		#pragma pack(push)
		#pragma pack(1)
		typedef struct
		{
			char	identsize;              // Size of ID field that follows header (0)
			char	colorMapType;           // 0 = None, 1 = paletted
			char	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
			unsigned short	colorMapStart;          // First colour map entry
			unsigned short	colorMapLength;         // Number of colors
			unsigned char 	colorMapBits;   // bits per palette entry
			unsigned short	xstart;                 // image x origin
			unsigned short	ystart;                 // image y origin
			unsigned short	width;                  // width in pixels
			unsigned short	height;                 // height in pixels
			char	bits;                   // bits per pixel (8 16, 24, 32)
			char	descriptor;             // image descriptor
		} TGAHEADER;
		#pragma pack(pop)

		class CTGA
		{
		public:
			CTGA();
			~CTGA();

			GLbyte *ReadTGABits(const char *filename);
			int GetWidth() const { return m_iWidth; }
			int GetHeight() const { return m_iHeight; }
			int GetComponents() const { return m_iComponents; }
			uint GetFormat() const { return m_uFormat; }
			unsigned long GetImageSize() { return m_lImageSize; }
		private:
			CString m_filename;
			TGAHEADER m_tgaHeader;
			unsigned long m_lImageSize;
			int m_iWidth;
			int m_iHeight;
			int m_iComponents;
			uint m_uFormat;
			GLbyte *m_pData;
		};
	}
}

#endif
