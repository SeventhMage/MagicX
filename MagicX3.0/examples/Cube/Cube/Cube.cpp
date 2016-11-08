#include "Cube.h"

CubeVertex::CubeVertex()
:halfWide(50)
{
	m_cubeVertex = new float[5 * 8];
	m_cubeIndices = new float[36];

	float vertice[] = {
		//position
		-halfWide, -halfWide, halfWide,
		0, 0,
		halfWide, -halfWide, halfWide,
		0, 1,
		halfWide, halfWide, halfWide,
		1, 1
		-halfWide, halfWide, halfWide,
		1, 0,

		-halfWide, -halfWide, -halfWide,
		1, 0,
		halfWide, -halfWide, -halfWide,
		0, 0,
		halfWide, halfWide, -halfWide,
		0, 1,
		-halfWide, halfWide, -halfWide,
		1, 1,
	};

	float indice[] = {
		//front
		0, 1, 2,
		0, 2, 3,

		//back
		5, 4, 6,
		5, 7, 6,
		//left
		0, 3, 7,
		0, 7, 4,
		//right
		1, 5, 6,
		1, 6, 2,
		//top
		2, 6, 7,
		2, 7, 3,
		//bottom
		0, 4, 5,
		0, 5, 1
	};

	memcpy(m_cubeVertex, vertice, sizeof(vertice));
	memcpy(m_cubeIndices, indice, sizeof(indice));
}

CubeVertex::~CubeVertex()
{
	delete[]m_cubeVertex;
	delete[]m_cubeIndices;
}

mx::scene::EVertexAttribute CubeVertex::GetVertexAttribute()
{
	return EVertexAttribute(VF_POSITION | VF_TEXCOORD);
}
