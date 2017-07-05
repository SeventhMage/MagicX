#ifndef _RENDER_S_COLOR_H_
#define _RENDER_S_COLOR_H_

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
		}Color;
	}
}

#endif