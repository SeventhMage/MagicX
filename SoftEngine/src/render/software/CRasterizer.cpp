#include "CRasterizer.h"
#include "base/base.h"

namespace se
{
	namespace render
	{

		CRasterizer::CRasterizer()
			:m_pDrawBuffer(nullptr)
			, m_bufferWidth(0)
			, m_bufferHeight(0)
		{

		}

		CRasterizer::~CRasterizer()
		{

		}


		void CRasterizer::SetBufferSize(uint width, uint height)
		{
			m_bufferWidth = width;
			m_bufferHeight = height;
		}


		void CRasterizer::DrawTriangle(const Triangle &triangle)
		{
			CVector2 p0(triangle.vTranslatePosition[0].x, triangle.vTranslatePosition[0].y);
			CVector2 p1(triangle.vTranslatePosition[1].x, triangle.vTranslatePosition[1].y);
			CVector2 p2(triangle.vTranslatePosition[2].x, triangle.vTranslatePosition[2].y);

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
					DrawBottomTriangle(p0, t0, c0, p2, t2, c2, p1, t1, c1);
			}
			else if (FLOAT_EQUAL(p1.y, p2.y))
			{
				if (p1.x < p0.x)
					DrawTopTriangle(p0, t0, c0, p1, t1, c1, p2, t2, c2);
				else
					DrawTopTriangle(p0, t0, c0, p2, t2, c2, p1, t1, c1);
			}
			else
			{

				CVector2 newPoint(p0.x + (p2.x - p0.x)*(p1.y - p0.y) / (p2.y - p0.y), p1.y);
				CVector2 newTexCoord(t0.x + (t2.x - t0.x)*(t2.y - t0.y) / (t1.y - t0.y), t1.y);
				float rate = newPoint.getDistanceFrom(p0) / p0.getDistanceFrom(p2);
				SColor newColor = GetInterpolation(p0, c0, p2, c2, rate);
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

		void CRasterizer::DrawTopTriangle(const CVector2 &p0,
			const CVector2 &t0, const render::SColor &c0, const CVector2 &p1, const CVector2 &t1, const render::SColor &c1, const CVector2 &p2, const CVector2 &t2, const render::SColor &c2)
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

				float lrate = CVector2(x0, i).getDistanceFrom(p0) / p0.getDistanceFrom(p1);
				float rrate = CVector2(x1, i).getDistanceFrom(p0) / p0.getDistanceFrom(p2);
				SColor lc = GetInterpolation(p0, c0, p1, c1, lrate);
				SColor rc = GetInterpolation(p0, c0, p2, c2, rrate);				
											
				FillColor(addr, x1 - x0, lc, rc);
			}
		}

		void CRasterizer::DrawBottomTriangle(const CVector2 &p0, const CVector2 &t0, const render::SColor &c0, const CVector2 &p1, const CVector2 &t1, const render::SColor &c1, const CVector2 &p2, const CVector2 &t2, const render::SColor &c2)
		{	
			float dx12 = (p1.x - p2.x) / (p1.y - p2.y);
			float dx02 = (p0.x - p2.x) / (p0.y - p2.y);

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

				float lrate = CVector2(x0, i).getDistanceFrom(p1) / p0.getDistanceFrom(p2);
				float rrate = CVector2(x1, i).getDistanceFrom(p0) / p0.getDistanceFrom(p2);
				SColor lc = GetInterpolation(p1, c1, p2, c2, lrate);
				SColor rc = GetInterpolation(p0, c0, p2, c2, rrate);

				FillColor(addr, x1 - x0, lc, rc);				
			}
		}

		se::render::SColor CRasterizer::GetInterpolation(const CVector2 &p0, const SColor &c0, 
			const CVector2 &p1, const SColor &c1, float rate)
		{			
			render::SColor color(c0.a * rate + c1.a * (1 - rate), c0.r * rate + c1.r * (1 - rate),
				c0.g * rate + c1.g * (1 - rate), c0.b * rate + c1.b * (1 - rate));
			return color;
		}

		void CRasterizer::FillColor(uint *addr, uint count, const SColor &c0, const SColor &c1)
		{
			for (uint i = 0; i < count; ++i)
			{
				float rate = 1.f * i / count;
				SColor color(c0.a * rate + c1.a * (1 - rate), c0.r * rate + c1.r * (1 - rate),
					c0.g * rate + c1.g * (1 - rate), c0.b * rate + c1.b * (1 - rate));
				*addr = color.Get32BitColor();
				++addr;
			}
		}

	}
}