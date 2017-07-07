#ifndef _RENDER_C_RASTERIZER_H_
#define _RENDER_C_RASTERIZER_H_

#include "base/base.h"
#include "math/CVector3.h"
#include "math/CVector2.h"
#include "../STriangleMesh.h"

namespace se
{
	namespace render
	{
		class CRasterizer
		{
		public:
			CRasterizer();
			~CRasterizer();
			
			static void DrawTriangle(uint *drawBuffer, uint width, uint height, const Triangle &triangle);
		private:
			static void DrawTopTriangle(uint *drawBuffer, uint width, uint height,
				const CVector2 &p0, const CVector2 &t0, const render::SColor &c0,
				const CVector2 &p1, const CVector2 &t1, const render::SColor &c1,
				const CVector2 &p2, const CVector2 &t2, const render::SColor &c2);
			static void DrawBottomTriangle(uint *drawBuffer, uint width, uint height,
				const CVector2 &p0, const CVector2 &t0, const render::SColor &c0,
				const CVector2 &p1, const CVector2 &t1, const render::SColor &c1,
				const CVector2 &p2, const CVector2 &t2, const render::SColor &c2);
		};
	}
}

#endif