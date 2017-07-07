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
			memset(vPosition, 0, sizeof(vPosition));
			memset(vTranslatePosition, 0, sizeof(vTranslatePosition));
			memset(vNormal, 0, sizeof(vNormal));
			memset(vTranslateNormal, 0, sizeof(vTranslateNormal));
			memset(vTexCoord, 0, sizeof(vTexCoord));
			memset(vertexColor, 0, sizeof(vertexColor));
		}

	}
}