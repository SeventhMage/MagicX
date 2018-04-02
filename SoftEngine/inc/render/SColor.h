#ifndef _RENDER_S_COLOR_H_
#define _RENDER_S_COLOR_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		typedef struct SColor
		{
			SColor()
			:a(1), r(0), g(0), b(0)
			{
			}
			SColor(float a, float r, float g, float b)
			:a(a), r(r), g(g), b(b)
			{

			}
			union
			{
				struct  
				{
					float a, r, g, b;
				};
				float c[4];
			};
			uint Get32BitColor() const
			{
				return ((uint(a * 0xFF))<<24) | ((uint(r * 0xFF))<<16) | ((uint(g * 0xFF))<<8) | (uint(b * 0xFF));
			}

			SColor &operator*=(float v)
			{
				for (uint i = 0; i < 4; ++i)
					c[i] *= v;
				return *this;
			}

			SColor &operator*=(const SColor &color)
			{
				for (uint i = 0; i < 4; ++i)
					c[i] *= color.c[i];
				return *this;
			}

			SColor &operator+=(const SColor &color)
			{
				for (uint i = 0; i < 4; ++i)
				{
					c[i] += color.c[i];
				}

				return *this;
			}

			SColor operator/(float v)const
			{
				SColor result;
				v = 1.f / v;
				for (uint i = 0; i < 4; ++i)
					result.c[i] = c[i] * v;
				return result;				
			}

			SColor operator*(float v)const
			{
				SColor result;
				for (uint i = 0; i < 4; ++i)
				{
					result.c[i] = c[i] * v;
				}
				return result;
			}

			SColor operator*(const SColor &color)const
			{
				SColor result;
				for (uint i = 0; i < 4; ++i)
				{
					result.c[i] = c[i] * color.c[i];
				}
				return result;
			}

			SColor operator+(const SColor &color)const
			{
				SColor result;
				for (uint i = 0; i < 4; ++i)
				{
					result.c[i] = c[i] + color.c[i];
				}
				return result;
			}

			SColor operator-(const SColor &color)const
			{
				SColor result;
				for (uint i = 0; i < 4; ++i)
				{
					result.c[i] = c[i] - color.c[i];
				}
				return result;
			}
		}Color;
	}
}

#endif