#include "STriangleMesh.h"

namespace se
{
	namespace render
	{


		STriangleMesh::STriangleMesh()						
		{
			Reset();
		}

		void STriangleMesh::Reset()
		{
			vertexAttr = 0;
			faceAttr = 0;

			for (int i = 0; i < 3; ++i)
			{
				vColor[i].x = vColor[i].y = vColor[i].z = 1.0f;
			}
		}

	}
}