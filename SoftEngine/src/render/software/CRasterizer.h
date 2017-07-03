#ifndef _RENDER_C_RASTERIZER_H_
#define _RENDER_C_RASTERIZER_H_

#include "base/seType.h"
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
			
			static void DrawTriangle(ubyte *drawBuffer, uint width, uint height, const Triangle &triangle);
		};
	}
}

#endif