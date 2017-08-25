#include "CRasterizer.h"
#include "base/base.h"

namespace se
{
	namespace render
	{

		CRasterizer::CRasterizer()
			:m_pDrawBuffer(nullptr)
			, m_pDepthBuffer(nullptr)
			, m_bufferWidth(0)
			, m_bufferHeight(0)
			, m_pTextureData(nullptr)
			, m_textureWidth(0)
			, m_textureHeight(0)
		{

		}

		CRasterizer::~CRasterizer()
		{

		}


		void CRasterizer::DrawTriangle(const Triangle &triangle)
		{
			CVector4 p0(triangle.vTranslatePosition[0].x, triangle.vTranslatePosition[0].y, triangle.vTranslatePosition[0].z, triangle.vTranslatePosition[0].w);
			CVector4 p1(triangle.vTranslatePosition[1].x, triangle.vTranslatePosition[1].y, triangle.vTranslatePosition[1].z, triangle.vTranslatePosition[1].w);
			CVector4 p2(triangle.vTranslatePosition[2].x, triangle.vTranslatePosition[2].y, triangle.vTranslatePosition[2].z, triangle.vTranslatePosition[2].w);

			CVector2 t0 = triangle.vTexCoord[0];
			CVector2 t1 = triangle.vTexCoord[1];
			CVector2 t2 = triangle.vTexCoord[2];

			render::SColor c0 = triangle.vertexColor[0];
			render::SColor c1 = triangle.vertexColor[1];
			render::SColor c2 = triangle.vertexColor[2];

			//÷±œﬂ
			if ((FLOAT_EQUAL(p0.y, p1.y) && FLOAT_EQUAL(p0.y, p2.y)) ||
				(FLOAT_EQUAL(p0.x, p1.x) && FLOAT_EQUAL(p0.x, p2.x)))
				return;

			//∞¥y÷µ¥”–°µΩ¥Û≈≈–Ú
			if (p1.y < p0.y)
			{
				base::swap(p0, p1);
				base::swap(t0, t1);
				base::swap(c0, c1);
			}

			if (p2.y < p1.y)
			{
				base::swap(p2, p1);
				base::swap(t2, t1);
				base::swap(c2, c1);
			}

			if (p1.y < p0.y)
			{
				base::swap(p0, p1);
				base::swap(t0, t1);
				base::swap(c0, c1);
			}

			if (FLOAT_EQUAL(p0.y, p1.y))
			{
				if (p1.x < p0.x)
					DrawBottomTriangle(p0, t0, c0, p1, t1, c1, p2, t2, c2);
				else
					DrawBottomTriangle(p1, t1, c1, p0, t0, c0, p2, t2, c2);
			}
			else if (FLOAT_EQUAL(p1.y, p2.y))
			{
				if (p1.x < p2.x)
					DrawTopTriangle(p0, t0, c0, p1, t1, c1, p2, t2, c2);
				else
					DrawTopTriangle(p0, t0, c0, p2, t2, c2, p1, t1, c1);
			}
			else
			{
				float newX = p0.x + (p2.x - p0.x)*(p1.y - p0.y) / (p2.y - p0.y);
				float p02Rate = CVector2(newX, p1.y).getDistanceFrom(CVector2(p0.x, p0.y))
					/ CVector2(p0.x, p0.y).getDistanceFrom(CVector2(p2.x, p2.y));

				float invNewZ = p0.z * (1 - p02Rate) + p2.z * p02Rate;
				float newW = (1 / p0.w) *  (1 - p02Rate) + (1 / p2.w) * p02Rate;

				CVector4 newPoint(newX, p1.y, invNewZ, 1 / newW);

				CVector2 newTexCoord = ((t0 / p0.w) * (1 - p02Rate) + (t2 / p2.w) * p02Rate) / newW;
				SColor newColor = (((c0 / p0.w) * (1 - p02Rate)) + ((c2 / p2.w) * p02Rate)) / newW;
				if (p1.x < newPoint.x)
				{			
					DrawTopTriangle(p0, t0, c0, p1, t1, c1, newPoint, newTexCoord, newColor);
					DrawBottomTriangle(newPoint, newTexCoord, newColor, p1, t1, c1, p2, t2, c2);
				}
				else
				{
					DrawTopTriangle(p0, t0, c0, newPoint, newTexCoord, newColor, p1, t1, c1);
					DrawBottomTriangle(p1, t1, c1, newPoint, newTexCoord, newColor, p2, t2, c2);
				}				
			}
		}

		void CRasterizer::DrawTopTriangle(const CVector4 &p0, const CVector2 &t0,
			const render::SColor &c0, const CVector4 &p1, const CVector2 &t1,
			const render::SColor &c1, const CVector4 &p2, const CVector2 &t2, const render::SColor &c2)
		{
			float dx01 = (p1.x - p0.x) / (p1.y - p0.y);
			float dx02 = (p2.x - p0.x) / (p2.y - p0.y);
			float x0 = p0.x;
			float x1 = p0.x;

			float ratel = sqrt(1 + dx01 * dx01);
			float rater = sqrt(1 + dx02 * dx02);

			float dzl = (p1.z - p0.z) / (p0.getDistanceFrom(p1));
			float dzr = (p2.z - p0.z) / (p0.getDistanceFrom(p2));
			dzl *= ratel;
			dzr *= rater;
			float zl = p0.z;
			float zr = p0.z;

			float dwl = (1 / p1.w - 1 / p0.w) / (p0.getDistanceFrom(p1));
			float dwr = (1 / p2.w - 1 / p0.w) / (p0.getDistanceFrom(p2));
			dwl *= ratel;
			dwr *= rater;
			float wl = 1 / p0.w;
			float wr = 1 / p0.w;

			SColor dcl = (c1 / p1.w - c0 / p0.w) / (p0.getDistanceFrom(p1));
			SColor dcr = (c2 / p2.w - c0 / p0.w) / (p0.getDistanceFrom(p2));
			dcl *= ratel;
			dcr *= rater;
			SColor cl = c0 * wl;
			SColor cr = c0 * wr;


			float dul = (t1.x / p1.w - t0.x / p0.w) / fabs(p1.x - p0.x);
			float dvl = (t1.y / p1.w - t0.y / p0.w) / fabs(p1.y - p0.y);
			float dur = (t2.x / p2.w - t0.x / p0.w) / fabs(p2.x - p0.x);
			float dvr = (t2.y / p2.w - t0.y / p0.w) / fabs(p2.y - p0.y);
			dul *= fabs(dx01);
			dur *= fabs(dx02);
			float ul = t0.x * wl;
			float vl = t0.y * wl;
			float ur = t0.x * wr;
			float vr = t0.y * wr;


			for (int i = (int)p0.y; i < (int)p2.y; ++i)
			{
				if (i<=0 || i>=m_bufferHeight)
					continue;

				if (x1 < x0)
					continue;

				if (x1 < 0 )
					continue;
				if (x0 > m_bufferWidth)
					continue;

				if (zl < -1 || zl > 1)
					continue;
				if (zr < -1 || zr > 1)
					continue;

				if (x0 < 0)
					x0 = 0;
				if (x1 > m_bufferWidth)
					x1 = m_bufferWidth;

				uint *addr = (uint *)m_pDrawBuffer + uint(x0 + (i - 1) * m_bufferWidth);				


				CVector2 tl(ul, vl);

				CVector2 tr(ur, vr);

				if (m_pDepthBuffer)
				{
					float *zbuffer = m_pDepthBuffer + int(x0 + (i - 1) * m_bufferWidth);
					if (m_pTextureData)
					{
						FillColor(addr, zbuffer, x0, zl, wl, x1, zr, wr, cl, cr , tl, tr);
					}
					else
						FillColor(addr, zbuffer, x0, zl, wl, x1, zr, wr, cl, cr);
				}
				else
					FillColor(addr, x1 - x0, cl, cr);

				zl += dzl;
				zr += dzr;

				wl += dwl;
				wr += dwr;

				x0 += dx01;
				x1 += dx02;

				ul += dul;
				vl += dvl;

				ur += dur;
				vr += dvr;

				cl += dcl;
				cr += dcr;
				
			}
		}

		void CRasterizer::DrawBottomTriangle(const CVector4 &p0, const CVector2 &t0, 
			const render::SColor &c0, const CVector4 &p1, const CVector2 &t1, 
			const render::SColor &c1, const CVector4 &p2, const CVector2 &t2, const render::SColor &c2)
		{	
			float dx12 = (p1.x - p2.x) / (p1.y - p2.y);
			float dx02 = (p0.x - p2.x) / (p0.y - p2.y);
			float x0 = p1.x;
			float x1 = p0.x;

			float ratel = sqrt(1 + dx12 * dx12);
			float rater = sqrt(1 + dx02 * dx02);
			float dzl = (p2.z - p1.z) / (p2.getDistanceFrom(p1));
			float dzr = (p2.z - p0.z) / (p2.getDistanceFrom(p0));
			dzl *= ratel;
			dzr *= rater;
			float zl = p1.z;
			float zr = p0.z;

			float dwl = (1 / p2.w - 1 / p1.w) / (p2.getDistanceFrom(p1));
			float dwr = (1 / p2.w - 1 / p0.w) / (p2.getDistanceFrom(p0));
			dwl *= ratel;
			dwr *= rater;
			float wl = 1 / p1.w;
			float wr = 1 / p0.w;

			SColor dcl = (c2 / p2.w - c1 / p1.w) / (p2.getDistanceFrom(p1));
			SColor dcr = (c2 / p2.w - c0 / p0.w) / (p2.getDistanceFrom(p0));
			dcl *= ratel;
			dcr *= rater;
			SColor cl = c1 * wl;
			SColor cr = c0 * wr;


			float dul = (t2.x / p2.w - t1.x / p1.w) / fabs(p2.x - p1.x);
			float dvl = (t2.y / p2.w - t1.y / p1.w) / fabs(p2.y - p1.y);
			float dur = (t2.x / p2.w - t0.x / p0.w) / fabs(p2.x - p0.x);
			float dvr = (t2.y / p2.w - t0.y / p0.w) / fabs(p2.y - p0.y);
			dul *= fabs(dx12);
			dur *= fabs(dx02);
			float ul = t1.x * wl;
			float vl = t1.y * wl;
			float ur = t0.x * wr;
			float vr = t0.y * wr;

			for (int i = (int)p0.y; i < (int)p2.y; ++i)
			{
				if (i<=0 || i>=m_bufferHeight)
					continue;

				if (x1 < x0)
					continue;

				if (x1 < 0)
					continue;
				if (x0 > m_bufferWidth)
					continue;

				if (zl < -1 || zl > 1)
					continue;
				if (zr < -1 || zr > 1)
					continue;

				if (x0 < 0)
					x0 = 0;
				if (x1 > m_bufferWidth)
					x1 = m_bufferWidth;

				uint *addr = (uint *)m_pDrawBuffer + uint(x0 + (i - 1) * m_bufferWidth);
				
				CVector2 tl(ul, vl);
				CVector2 tr(ur, vr);

				if (m_pDepthBuffer)
				{
					float *zbuffer = m_pDepthBuffer + int(x0 + (i - 1) * m_bufferWidth);
					if (m_pTextureData)
						FillColor(addr, zbuffer, x0, zl, wl, x1, zr, wr, cl, cr, tl, tr);
					else
						FillColor(addr, zbuffer, x0, zl, wl, x1, zr, wr, cl, cr);
				}
				else
					FillColor(addr, x1 - x0 + 1, cl, cr);
				
				zl += dzl;
				zr += dzr;

				wl += dwl;
				wr += dwr;
				
				x0 += dx12;
				x1 += dx02;

				cl += dcl;
				cr += dcr;

				ul += dul;
				vl += dvl;
				ur += dur;
				vr += dvr;
			}
		}

		se::render::SColor CRasterizer::GetInterpolation(const SColor &c0,const SColor &c1, float rate)
		{			
			render::SColor color(c0.a * (1 - rate) + c1.a * rate, c0.r * (1 - rate) + c1.r * rate,
				c0.g * (1 - rate) + c1.g * rate, c0.b * (1 - rate) + c1.b * rate);
			return color;
		}

		void CRasterizer::FillColor(uint *addr, uint count, const SColor &c0, const SColor &c1)
		{
			for (uint i = 0; i < count; ++i)
			{
				float rate = 1.f * i / count;
				SColor color = GetInterpolation(c0, c1, rate);
				*addr = color.Get32BitColor();
				++addr;
			}
		}

		void CRasterizer::FillColor(uint *addr, float *zbuffer, uint x0, float z0, float wl,
			uint x1, float z1, float wr, const SColor &c0, const SColor &c1)
		{
			int count = x1 - x0 + 1;
			float dz = (z1 - z0) / count;
			float z = z0;
			float dw = (wr - wl) / count;
			float w = wl;
			SColor dc = (c1 - c0) / count;
			SColor c = c0;
			for (uint i = 0; i < count; ++i)
			{
				if (z < *zbuffer) //’‚¿Ôµƒz∆‰ µ «1/z
				{
					SColor color = c / w;
					*addr = color.Get32BitColor();
					*zbuffer = z;
				}

				z += dz;
				w += dw;
				c += dc;

				++zbuffer;
				++addr;
			}
		}

		void CRasterizer::FillColor(uint *addr, float *zbuffer, uint x0, float z0, float wl,
			uint x1, float z1, float wr, const SColor &lc, const SColor &rc, const CVector2 &lt, const CVector2 &rt)
		{
			int count = x1 - x0 + 1;
			float dz = (z1 - z0) / count;
			float z = z0;
			float dw = (wr - wl) / count;
			float w = wl;
			SColor dc = (rc - lc) / count;
			SColor c = lc;
			float du = (rt.x - lt.x) / count;
			float dv = (rt.y - lt.y) / count;
			
			float u = lt.x;
			float v = lt.y;
			for (uint i = 0; i < count; ++i)
			{
				if (z < *zbuffer) //This z is 1/z in fact.
				{	
					int tx = (u / w) * (m_textureWidth - 1); //float calculate can't multiply 3 here.
					int ty = (1 - (v / w)) * (m_textureHeight - 1);
					SColor color = c / w;
					//uint tc = (0xff << 24) | uint((*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3)) * color.b )
					//	| (uint(*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3 + 1) * color.g) << 8)
					//	| (uint(*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3 + 2) * color.r) << 16);

					uint tc = (0xff << 24) | uint((*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3)))
						| (uint(*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3 + 1)) << 8)
						| (uint(*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3 + 2)) << 16);

					*addr = tc;
					*zbuffer = z;
				}

				z += dz;
				w += dw;
				c += dc;
				u += du;
				v += dv;

				++zbuffer;
				++addr;
			}
		}

		void CRasterizer::SetTextureInfo(ubyte *textureData, int width, int height)
		{
			m_pTextureData = textureData;
			m_textureWidth = width;
			m_textureHeight = height;
		}

		void CRasterizer::SetDrawBuffer(uint *pDrawBuffer, int width, int height)
		{
			m_pDrawBuffer = pDrawBuffer;
			m_bufferWidth = width;
			m_bufferHeight = height;
		}

	}
}
