#ifndef _RENDER_S_TRIANGLE_MESH_H_
#define _RENDER_S_TRIANGLE_MESH_H_

#include "math/CVector3.h"
#include "math/CVector2.h"
#include "base/SColor.h"

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
			base::SColor vertColor[3];
		}TriangleFace;

		typedef struct STriangleMesh
		{
			STriangleMesh();
			void Reset();
			int vertexAttr;			
			CVector3 vPosition[3];
			CVector3 vTranslatePosition[3];			
			CVector3 vNormal[3];
			CVector3 vTranslateNormal[3];
			CVector2 vTexCoord[3];
			base::SColor vertexColor[3];
		}Triangle;

		typedef std::vector<Triangle> TriangleList;
	}
}

#endif