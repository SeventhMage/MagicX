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
			CVector3 p0(triangle.vTranslatePosition[0].x, triangle.vTranslatePosition[0].y, triangle.vTranslatePosition[0].z);
			CVector3 p1(triangle.vTranslatePosition[1].x, triangle.vTranslatePosition[1].y, triangle.vTranslatePosition[1].z);
			CVector3 p2(triangle.vTranslatePosition[2].x, triangle.vTranslatePosition[2].y, triangle.vTranslatePosition[2].z);

			CVector2 t0 = triangle.vTexCoord[0];
			CVector2 t1 = triangle.vTexCoord[1];
			CVector2 t2 = triangle.vTexCoord[2];

			render::SColor c0 = triangle.vertexColor[0];
			render::SColor c1 = triangle.vertexColor[1];
			render::SColor c2 = triangle.vertexColor[2];

			//直线
			if ((FLOAT_EQUAL(p0.y, p1.y) && FLOAT_EQUAL(p0.y, p2.y)) ||
				(FLOAT_EQUAL(p0.x, p1.x) && FLOAT_EQUAL(p0.x, p2.x)))
				return;

			//按y值从小到大排序
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

				CVector3 newPoint(newX, p1.y, invNewZ);						

				CVector2 newTexCoord = (t0 * p0.z * (1 - p02Rate) + t2 * p2.z * p02Rate) / invNewZ;
				float rate = newPoint.getDistanceFrom(p0) / p0.getDistanceFrom(p2);
				SColor newColor = GetInterpolation(c0, c2, 1 - rate);
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

		void CRasterizer::DrawTopTriangle(const CVector3 &p0, const CVector2 &t0, 
			const render::SColor &c0, const CVector3 &p1, const CVector2 &t1, 
			const render::SColor &c1, const CVector3 &p2, const CVector2 &t2, const render::SColor &c2)
		{
			float dx01 = (p0.x - p1.x) / (p0.y - p1.y);
			float dx02 = (p0.x - p2.x) / (p0.y - p2.y);

			for (int i = (int)p0.y; i < (int)p2.y; ++i)
			{
				if (i<=0 || i>=m_bufferHeight)
					continue;
				int x0 = p0.x + (i - (int)p0.y) * dx01;
				int x1 = p0.x + (i - (int)p0.y) * dx02;								

				if (x1 < x0)
					continue;

				if (x1 < 0 )
					continue;
				if (x0 > m_bufferWidth)
					continue;

				if (x0 < 0)
					x0 = 0;
				if (x1 > m_bufferWidth)
					x1 = m_bufferWidth;

				uint *addr = (uint *)m_pDrawBuffer + uint(x0 + (i - 1) * m_bufferWidth);				
				//std::fill_n(addr, uint(x1 - x0), color);

				float lrate = CVector2(x0, i).getDistanceFrom(CVector2(p0.x, p0.y)) / CVector2(p0.x, p0.y).getDistanceFrom(CVector2(p1.x, p1.y));
				float rrate = CVector2(x1, i).getDistanceFrom(CVector2(p0.x, p0.y)) / CVector2(p0.x, p0.y).getDistanceFrom(CVector2(p2.x, p2.y));
				SColor lc = GetInterpolation(c0, c1, 1 - lrate);
				SColor rc = GetInterpolation(c0, c2, 1 - rrate);				
				
				float z0 = p0.z * (1 - lrate) + p1.z * lrate;
				float z1 = p0.z * (1 - rrate) + p2.z * rrate;

				CVector2 tl = (t0 * p0.z * (1 - lrate) + t1 * p1.z * lrate) / z0;
				CVector2 tr = (t0 * p0.z * (1 - rrate) + t2 * p2.z * rrate) / z1;

				CVector2 tl_ = (t0 * (1 - lrate) + t1 * lrate);
				CVector2 tr_ = (t0 * (1 - rrate) + t2 * rrate);

				if (m_pDepthBuffer)
				{
					float *zbuffer = m_pDepthBuffer + int(x0 + (i - 1) * m_bufferWidth);
					if (m_pTextureData)
					{
						FillColor(addr, zbuffer, x0, z0, x1, z1, lc, rc, tl, tr);
					}
					else
						FillColor(addr, zbuffer, x0, z0, x1, z1, lc, rc);
				}
				else
					FillColor(addr, x1 - x0, lc, rc);
				
			}
		}

		void CRasterizer::DrawBottomTriangle(const CVector3 &p0, const CVector2 &t0, 
			const render::SColor &c0, const CVector3 &p1, const CVector2 &t1, 
			const render::SColor &c1, const CVector3 &p2, const CVector2 &t2, const render::SColor &c2)
		{	
			float dx12 = (p1.x - p2.x) / (p1.y - p2.y);
			float dx02 = (p0.x - p2.x) / (p0.y - p2.y);

			//float du12 = (t2.x * p2.z - t1.x * p1.z) / (p2.x - p1.x);
			//float dv12 = (t1.y * p1.z - t2.y * p2.z) / (p2.y - p1.y);
			//
			//float du02 = (t2.x * p2.z - t0.x * p0.z) / (p2.x - p0.x);
			//float dv02 = (t0.y * p0.z - t2.y * p2.z) / (p2.y - p0.y);

			for (int i = (int)p0.y; i < (int)p2.y; ++i)
			{
				if (i<=0 || i>=m_bufferHeight)
					continue;
				int x0 = p1.x + (i - (int)p1.y) * dx12;
				int x1 = p0.x + (i - (int)p0.y) * dx02;

				if (x1 < x0)
					continue;

				if (x1 < 0)
					continue;
				if (x0 > m_bufferWidth)
					continue;

				if (x0 < 0)
					x0 = 0;
				if (x1 > m_bufferWidth)
					x1 = m_bufferWidth;


				uint *addr = (uint *)m_pDrawBuffer + uint(x0 + (i - 1) * m_bufferWidth);
				
				//std::fill_n(addr, uint(x1 - x0), color);

				float lrate = CVector2(x0, i).getDistanceFrom(CVector2(p1.x, p1.y)) / CVector2(p1.x, p1.y).getDistanceFrom(CVector2(p2.x, p2.y));
				float rrate = CVector2(x1, i).getDistanceFrom(CVector2(p0.x, p0.y)) / CVector2(p0.x, p0.y).getDistanceFrom(CVector2(p2.x, p2.y));
				SColor lc = GetInterpolation(c1, c2, 1 - lrate);
				SColor rc = GetInterpolation(c0, c2, 1 - rrate);

				float z0 = p1.z * (1 - lrate) + p2.z * lrate;
				float z1 = p0.z * (1 - rrate) + p2.z * rrate;
	

				CVector2 tl = (t1 * p1.z * (1 - lrate) + t2 * p2.z * lrate) / z0;
				CVector2 tr = (t0 * p0.z * (1 - rrate) + t2 * p2.z * rrate) / z1;

				CVector2 tl_ = t1 * (1 - lrate) + t2 * lrate;
				CVector2 tr_ = t0 * (1 - rrate) + t2 * rrate;

				if (m_pDepthBuffer)
				{
					float *zbuffer = m_pDepthBuffer + int(x0 + (i - 1) * m_bufferWidth);
					if (m_pTextureData)
						FillColor(addr, zbuffer, x0, z0, x1, z1, lc, rc, tl, tr);
					else
						FillColor(addr, zbuffer, x0, z0, x1, z1, lc, rc);
				}
				else
					FillColor(addr, x1 - x0 + 1, lc, rc);
				
			}
		}

		se::render::SColor CRasterizer::GetInterpolation(const SColor &c0,const SColor &c1, float rate)
		{			
			render::SColor color(c0.a * rate + c1.a * (1 - rate), c0.r * rate + c1.r * (1 - rate),
				c0.g * rate + c1.g * (1 - rate), c0.b * rate + c1.b * (1 - rate));
			return color;
		}

		void CRasterizer::FillColor(uint *addr, uint count, const SColor &c0, const SColor &c1)
		{
			for (uint i = 0; i < count; ++i)
			{
				float rate = 1.f - 1.f * i / count;
				SColor color(c0.a * rate + c1.a * (1 - rate), c0.r * rate + c1.r * (1 - rate),
					c0.g * rate + c1.g * (1 - rate), c0.b * rate + c1.b * (1 - rate));
				*addr = color.Get32BitColor();
				++addr;
			}
		}

		void CRasterizer::FillColor(uint *addr, float *zbuffer, uint x0, float z0, uint x1, float z1, const SColor &c0, const SColor &c1)
		{
			int count = x1 - x0 + 1;
			for (uint i = 0; i < count; ++i)
			{
				float rate = 1.f - 1.f * i / count;
				float z = z0 * rate + z1 * (1 - rate);

				if (z < *zbuffer) //这里的z其实是1/z
				{
					SColor color(c0.a * rate + c1.a * (1 - rate), c0.r * rate + c1.r * (1 - rate),
						c0.g * rate + c1.g * (1 - rate), c0.b * rate + c1.b * (1 - rate));

					*addr = color.Get32BitColor();
					*zbuffer = z;
				}

				++zbuffer;
				++addr;
			}
		}

		void CRasterizer::FillColor(uint *addr, float *zbuffer, uint x0, float z0, uint x1, float z1, const SColor &lc, const SColor &rc, const CVector2 &lt, const CVector2 &rt)
		{
			int count = x1 - x0 + 1;
			for (uint i = 0; i < count; ++i)
			{
				float rate = 1.f - 1.f * i / count;
				float z = z0 * rate + z1 * (1 - rate);				

				if (z < *zbuffer) //这里的z其实是1/z
				{
					SColor color(lc.a * rate + rc.a * (1 - rate), lc.r * rate + rc.r * (1 - rate),
						lc.g * rate + rc.g * (1 - rate), lc.b * rate + rc.b * (1 - rate));
										
					CVector2 t = (lt * z0 * rate + rt * z1 *(1 - rate)) / z;
					CVector2 t_ = lt * rate + rt * (1 - rate);
					int tx = t.x * m_textureWidth; //浮点运算，不能在这里直接乘3
					int ty = (1 - t.y) * m_textureHeight;
					uint tc = (0xff << 24) | ((*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3 + 0)))
						| ((*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3 + 1)) << 8)
						| ((*(m_pTextureData + ty * m_textureWidth * 3 + tx * 3 + 2)) << 16);

					*addr = tc;// color.Get32BitColor();
					*zbuffer = z;
				}

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