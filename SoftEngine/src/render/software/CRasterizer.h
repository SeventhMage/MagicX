#ifndef _RENDER_C_RASTERIZER_H_
#define _RENDER_C_RASTERIZER_H_

#include "base/base.h"
#include "math/CVector3.h"
#include "math/CVector3.h"
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
			
			void SetDrawBuffer(uint *pDrawBuffer, int width, int height);
			void SetDepthBuffer(float *pDrawBuffer){ m_pDepthBuffer = pDrawBuffer; }			

			void SetTextureInfo(ubyte *textureData, int width, int height);

			void DrawTriangle(const Triangle &triangle);
		private:
			void DrawTopTriangle(const CVector4 &p0, const CVector2 &t0, const render::SColor &c0,
				const CVector4 &p1, const CVector2 &t1, const render::SColor &c1,
				const CVector4 &p2, const CVector2 &t2, const render::SColor &c2);
			void DrawBottomTriangle(const CVector4 &p0, const CVector2 &t0, const render::SColor &c0,
				const CVector4 &p1, const CVector2 &t1, const render::SColor &c1,
				const CVector4 &p2, const CVector2 &t2, const render::SColor &c2);
			SColor GetInterpolation(const SColor &c0,const SColor &c1, float rate);

			void FillColor(uint *addr, uint count, const SColor &lc, const SColor &rc);
			void FillColor(uint *addr, float *zbuffer, uint x0, float z0, float wl, uint x1, float z1, float wr, const SColor &lc, const SColor &rc);
			void FillColor(uint *addr, float *zbuffer, uint x0, float z0, float wl, uint x1, float z1, float wr,  const SColor &lc, const SColor &rc, const CVector2 &lt, const CVector2 &rt);
		private:
			uint *m_pDrawBuffer;
			float *m_pDepthBuffer;
			int m_bufferWidth;
			int m_bufferHeight;

			ubyte *m_pTextureData;
			int m_textureWidth;
			int m_textureHeight;
		};
	}
}

#endif