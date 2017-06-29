#ifndef _RENDER_C_RASTERIZER_H_
#define _RENDER_C_RASTERIZER_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		class CRasterizer
		{
		public:
			CRasterizer();
			~CRasterizer();

			static void DrawTirangle(ubyte *destAddr, uint width, uint height, int x1, int y1, int c1, 
				int x2, int y2, int c2, int x3, int y3, int c3);
			static void DrawTriangle(ubyte *destAddr, int *colorPlate, int x1, int tx1, int y1, int ty1,
				int x2, int tx2, int y2, int ty2, int x3, int tx3, int y3, int ty3);
		};
	}
}

#endif