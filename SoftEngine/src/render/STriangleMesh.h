#ifndef _RENDER_S_TRIANGLE_MESH_H_
#define _RENDER_S_TRIANGLE_MESH_H_

#include "math/CVector4.h"
#include "math/CVector3.h"
#include "math/CVector2.h"
#include "render/SColor.h"

#include <vector>


namespace se
{
	namespace render
	{
		using namespace math;

		enum EFaceAttribute
		{			
			FA_BACKFACE = 1,
		};

		typedef struct STriangleFace
		{
			CVector3 vPosition[3];
			CVector3 vNormal[3];
			CVector2 vTexCoord[3];
			SColor vertColor[3];
		}TriangleFace;

		typedef struct STriangleMesh
		{
			STriangleMesh();
			void Reset();			
			CVector3 vPosition[3];
			CVector4 vTranslatePosition[3];			
			CVector3 vNormal[3];
			CVector3 vTranslateNormal[3];
			CVector2 vTexCoord[3];
			SColor vertexColor[3];
		}Triangle;

		typedef std::vector<Triangle> TriangleList;
	}
}

#endif