#ifndef _RENDER_S_VERTEX_H_
#define _RENDER_S_VERTEX_H_

#include "math/CVector2.h"
#include "math/CVector3.h"
#include "SColor.h"

#include <vector>

namespace se
{
	namespace render
	{
		typedef struct SVertex
		{
			math::CVector3 position;
			math::CVector3 normal;
			math::CVector2 texCoord;
			Color color;
		}Vertex;

		//typedef std::vector<Vertex>Vertices;
	}
}

#endif