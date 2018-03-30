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
		
		class FragmentParam
		{		
		public:
			FragmentParam(const Color &color)
				:color(color)
			{

			}
			virtual ~FragmentParam(){}


			const Color &color;
		};
		
		class FragmentParam_1 : public FragmentParam
		{
		public:
			FragmentParam_1(const Color &c)
				:FragmentParam(c)
			{
			}						
		};
		
		class FragmentParam_2 : public FragmentParam
		{
		public:
			FragmentParam_2(const Color &c, const CVector2 &texCoord)
				:FragmentParam(c), texCoord(texCoord)
			{
			}
			
			const CVector2 &texCoord;
		};

		class CalcFragmentFunc
		{
		public:			
			virtual Color operator()(const FragmentParam &param) const = 0;	
		};
				
		
		class FragmentCalcFunc
		{
		public:			
			FragmentCalcFunc()
				:func(nullptr)
			{
			}

			void BindFunc(const CalcFragmentFunc *func)
			{
				this->func = func;
			}

			Color operator()(const FragmentParam &param)
			{
				if (func)
					return (*func)(param);
				return param.color;
			}

		private:			
			const CalcFragmentFunc *func;
		};

		
		class CSoftRenderer;

		class CRasterizer
		{
		public:

			typedef Color(*CalcFragment_1)(const Color &);
			typedef Color(*CalcFragment_2)(const Color &, const CVector2 &);

			CRasterizer();
			~CRasterizer();
			
			void SetDrawBuffer(uint *pDrawBuffer, int width, int height);
			void SetDepthBuffer(float *pDrawBuffer){ m_pDepthBuffer = pDrawBuffer; }			

			void SetTextureInfo(ubyte *textureData, int width, int height);

			void BindFragmentFunc(const CalcFragmentFunc &func);

			void DrawTriangle(const Triangle &triangle);
			void DrawLine(int x0, int y0, int x1, int y1, const SColor &c = SColor(1, 0, 0, 0));
			void DrawCircle(int xcenter, int ycenter, int radius, const SColor &c = SColor(1, 0, 0, 0));
			void DrawEllipse(int xc, int yc, int a, int b, const render::SColor &c = SColor(1, 0, 0, 0));
			void DrawPixel(int x, int y, const SColor &c);
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
			
			FragmentCalcFunc m_FragmentCalcFunc;
		};
	}
}

#endif