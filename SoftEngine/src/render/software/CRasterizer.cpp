#include "CRasterizer.h"
#include "base/base.h"

namespace se
{
	namespace render
	{

		CRasterizer::CRasterizer()
		{

		}

		CRasterizer::~CRasterizer()
		{

		}

		void CRasterizer::DrawTriangle(uint *drawBuffer, uint width, uint height, const Triangle &triangle)
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
				DrawBottomTriangle(drawBuffer, width, height, p0, t0, c0, p1, t1, c1, p2, t2, c2);
			}
			else if (FLOAT_EQUAL(p1.y, p2.y))
			{
				DrawTopTriangle(drawBuffer, width, height, p0, t0, c0, p1, t1, c1, p2, t2, c2);
			}
			else
			{
				float px = p0.x + (p1.y - p0.y)*(p2.x - p0.x) / (p2.y - p0.y);
				CVector2 newPoint(px, p1.y);
				
				float tx = t0.x + (t1.y - t0.y)*(t2.x - t0.x) / (t2.y - p0.y);
				CVector2 newTexCoord(tx, t1.y);

				float rate = newPoint.getDistanceFrom(p0) / p0.getDistanceFrom(p1);

				render::SColor newColor(c0.a * rate + c2.a * (1 - rate), c0.r * rate + c2.r * (1 - rate), 
					c0.g * rate + c2.g * (1 - rate), c0.b * rate + c2.b * (1 - rate));

				DrawTopTriangle(drawBuffer, width, height, p0, t0, c0, p1, t1, c1, newPoint, newTexCoord, newColor);
				DrawBottomTriangle(drawBuffer, width, height, p1, t1, c1, newPoint, newTexCoord, newColor, p2, t2, c2);
			}
		}

		void CRasterizer::DrawTopTriangle(uint *drawBuffer, uint width, uint height, const CVector2 &p0,
			const CVector2 &t0, const render::SColor &c0, const CVector2 &p1, const CVector2 &t1, const render::SColor &c1, const CVector2 &p2, const CVector2 &t2, const render::SColor &c2)
		{
			uint color = 0xFF << 24;
			color += (std::rand() % 0xFE + 1) << 16;
			color += (std::rand() % 0xFE + 1) << 8;
			color += std::rand() % 0xFE + 1;
			float dx01 = (p0.x - p1.x) / (p0.y - p1.y);
			float dx02 = (p0.x - p2.x) / (p0.y - p2.y);

			for (int i = (int)p0.y; i < (int)p2.y; ++i)
			{
				if (i<=0 || i>=height)
					continue;
				int x0 = p0.x + (i - (int)p0.y) * dx01;
				int x1 = p0.x + (i - (int)p0.y) * dx02;

				if (x1 < x0)
					base::swap(x0, x1);

				if (x0 < 0)
					x0 = 0;
				if (x1 > width)
					x1 = width;

				if (x1 < x0)
					base::swap(x0, x1);

				uint *addr = (uint *)drawBuffer + uint(x0 + (i - 1) * width);
				std::fill_n(addr, uint(x1 - x0), color);
			}
		}

		void CRasterizer::DrawBottomTriangle(uint *drawBuffer, uint width, uint height, const CVector2 &p0, const CVector2 &t0, const render::SColor &c0, const CVector2 &p1, const CVector2 &t1, const render::SColor &c1, const CVector2 &p2, const CVector2 &t2, const render::SColor &c2)
		{	
			uint color = 0xFF << 24;
			color += (std::rand() % 0xFE + 1) << 16;
			color += (std::rand() % 0xFE + 1) << 8;
			color += std::rand() % 0xFE + 1;

			float dx12 = (p1.x - p2.x) / (p1.y - p2.y);
			float dx02 = (p0.x - p2.x) / (p0.y - p2.y);

			for (int i = (int)p0.y; i < (int)p2.y; ++i)
			{
				if (i<=0 || i>=height)
					continue;
				int x0 = p1.x + (i - (int)p1.y) * dx12;
				int x1 = p0.x + (i - (int)p0.y) * dx02;

				if (x1 < x0)
					base::swap(x0, x1);

				if (x0 < 0)
					x0 = 0;
				if (x1 > width)
					x1 = width;
				if (x1 < x0)
					base::swap(x0, x1);

				uint *addr = (uint *)drawBuffer + uint(x0 + (i - 1) * width);				
				std::fill_n(addr, uint(x1 - x0), color);
			}
		}

	}
}