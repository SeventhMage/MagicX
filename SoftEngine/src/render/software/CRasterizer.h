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
			
			void SetDrawBuffer(uint *pDrawBuffer){ m_pDrawBuffer = pDrawBuffer; }
			void SetBufferSize(uint width, uint height);			

			void DrawTriangle(const Triangle &triangle);
		private:
			void DrawTopTriangle(const CVector2 &p0, const CVector2 &t0, const render::SColor &c0,
				const CVector2 &p1, const CVector2 &t1, const render::SColor &c1,
				const CVector2 &p2, const CVector2 &t2, const render::SColor &c2);
			void DrawBottomTriangle(const CVector2 &p0, const CVector2 &t0, const render::SColor &c0,
				const CVector2 &p1, const CVector2 &t1, const render::SColor &c1,
				const CVector2 &p2, const CVector2 &t2, const render::SColor &c2);
			SColor GetInterpolation(const CVector2 &p0, const SColor &c0, const CVector2 &p1,
				const SColor &c1, float rate);

			void FillColor(uint *addr, uint count, const SColor &lc, const SColor &rc);
		private:
			uint *m_pDrawBuffer;
			uint m_bufferWidth;
			uint m_bufferHeight;
		};
	}
}

#endif