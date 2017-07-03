#ifndef _RENDER_S_TRIANGLE_MESH_H_
#define _RENDER_S_TRIANGLE_MESH_H_

#include "render/IMesh.h"
#include "math/CVector3.h"
#include "math/CVector2.h"

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

		typedef struct STriangleMesh : public IMesh
		{
			STriangleMesh();
			void Reset();
			int vertexAttr;
			int faceAttr;
			CVector3 vPosition[3];
			CVector3 vTranslatePosition[3];
			CVector3 vColor[3];
			CVector3 vNormal[3];
			CVector3 vTranslateNormal[3];
			CVector2 vTexCoord[3];
		}Triangle;

		typedef std::vector<Triangle> TriangleList;
	}
}

#endif